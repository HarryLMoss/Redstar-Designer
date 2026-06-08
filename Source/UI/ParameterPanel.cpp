/*
    ParameterPanel.cpp
    Implementation of the amp control panel.
*/

#include "ParameterPanel.h"

ParameterPanel::ParameterPanel(AmpState& state)
    : ampState(state)
{
    // Define the five controls: parameter ID + display label.
    const std::pair<juce::Identifier, juce::String> params[] = {
        { IDs::gain,   "Gain"   },
        { IDs::bass,   "Bass"   },
        { IDs::mid,    "Mid"    },
        { IDs::treble, "Treble" },
        { IDs::master, "Master" }
    };

    for (const auto& [id, name] : params)
    {
        auto control = std::make_unique<Control>();
        control->paramID = id;

        // Configure the rotary slider (0.0 - 1.0 range).
        control->slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        control->slider.setRange(0.0, 1.0, 0.001);
        control->slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 18);
        control->slider.addListener(this);
        addAndMakeVisible(control->slider);

        // Configure the label beneath it.
        control->label.setText(name, juce::dontSendNotification);
        control->label.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(control->label);

        controls.push_back(std::move(control));
    }

    // Start listening to the state so we react to external changes (presets).
    ampState.getTree().addListener(this);

    // Initialise slider positions from the current state.
    refreshAllFromState();
}

ParameterPanel::~ParameterPanel()
{
    // Stop listening before destruction to avoid dangling callbacks.
    ampState.getTree().removeListener(this);
}

void ParameterPanel::resized()
{
    // Lay the five controls out in a horizontal row.
    auto area = getLocalBounds().reduced(10);
    const int controlWidth = area.getWidth() / (int) controls.size();

    for (auto& control : controls)
    {
        auto column = area.removeFromLeft(controlWidth);
        control->label.setBounds(column.removeFromTop(20));
        control->slider.setBounds(column.reduced(5));
    }
}

void ParameterPanel::sliderValueChanged(juce::Slider* slider)
{
    // If we're the ones updating the slider (from a state change),
    // don't write back to the tree — that would cause a feedback loop.
    if (isUpdatingFromState)
        return;

    // Find which control owns this slider and write its value to the state.
    for (auto& control : controls)
    {
        if (&control->slider == slider)
        {
            ampState.set(control->paramID, (float) slider->getValue());
            break;
        }
    }
}

void ParameterPanel::valueTreePropertyChanged(juce::ValueTree&,
                                              const juce::Identifier& property)
{
    // A property changed in the state — update the matching slider.
    for (auto& control : controls)
    {
        if (control->paramID == property)
        {
            isUpdatingFromState = true;
            control->slider.setValue(ampState.get(property),
                                     juce::dontSendNotification);
            isUpdatingFromState = false;
            break;
        }
    }
}

void ParameterPanel::refreshAllFromState()
{
    isUpdatingFromState = true;
    for (auto& control : controls)
        control->slider.setValue(ampState.get(control->paramID),
                                 juce::dontSendNotification);
    isUpdatingFromState = false;
}