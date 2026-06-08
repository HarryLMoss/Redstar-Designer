/*
    ParameterPanel.h
    A panel of five rotary sliders representing the amp controls.

    This component is bound to the AmpState ValueTree in both directions:
      - User moves a slider  -> writes the new value into the ValueTree
      - ValueTree changes     -> updates the slider position to match
        (e.g. when a preset is loaded)

    It listens to the ValueTree via juce::ValueTree::Listener so it always
    reflects the current state, regardless of what changed it.
*/

#pragma once

#include <JuceHeader.h>
#include "../Domain/AmpState.h"

class ParameterPanel : public juce::Component,
                       private juce::Slider::Listener,
                       private juce::ValueTree::Listener
{
public:
    explicit ParameterPanel(AmpState& state);
    ~ParameterPanel() override;

    void resized() override;

private:
    // Called when the user drags a slider — writes to the ValueTree.
    void sliderValueChanged(juce::Slider* slider) override;

    // Called when any ValueTree property changes — updates the matching slider.
    void valueTreePropertyChanged(juce::ValueTree& tree,
                                  const juce::Identifier& property) override;

    // Pulls all current values from the state into the sliders.
    void refreshAllFromState();

    // Groups a slider with its label and the parameter ID it controls.
    struct Control
    {
        juce::Slider slider;
        juce::Label  label;
        juce::Identifier paramID;
    };

    // One Control per amp parameter.
    std::vector<std::unique_ptr<Control>> controls;

    AmpState& ampState;

    // Guard flag: prevents a feedback loop when we update a slider
    // programmatically (which would otherwise fire sliderValueChanged
    // and write back to the tree, which would fire this again, etc.)
    bool isUpdatingFromState = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParameterPanel)
};