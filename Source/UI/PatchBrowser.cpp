/*
    PatchBrowser.cpp
    Implementation of the preset browser UI.
*/

#include "PatchBrowser.h"

PatchBrowser::PatchBrowser(PresetLibrary& lib, AmpState& state)
    : library(lib), ampState(state)
{
    listBox.setModel(this);
    addAndMakeVisible(listBox);
    addAndMakeVisible(saveButton);
    addAndMakeVisible(randomButton);

    // Save the current amp state as a new preset.
    saveButton.onClick = [this]
    {
        auto name = "Preset " + juce::String(library.getNumPresets() + 1);
        library.addPreset(name, ampState);
    };

    // Add a randomised preset.
    randomButton.onClick = [this]
    {
        library.addRandomPreset();
    };

    library.addChangeListener(this);
}

PatchBrowser::~PatchBrowser()
{
    library.removeChangeListener(this);
}

void PatchBrowser::resized()
{
    auto area = getLocalBounds().reduced(8);

    auto buttonRow = area.removeFromBottom(30);
    saveButton.setBounds(buttonRow.removeFromLeft(buttonRow.getWidth() / 2).reduced(2));
    randomButton.setBounds(buttonRow.reduced(2));

    listBox.setBounds(area);
}

int PatchBrowser::getNumRows()
{
    return library.getNumPresets();
}

void PatchBrowser::paintListBoxItem(int row, juce::Graphics& g,
                                    int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
        g.fillAll(juce::Colours::darkorange.withAlpha(0.5f));

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawText(library.getPresetName(row),
               8, 0, width - 8, height,
               juce::Justification::centredLeft);
}

void PatchBrowser::listBoxItemClicked(int row, const juce::MouseEvent&)
{
    // Loading a preset writes its values into the AmpState, which the
    // ParameterPanel observes — so the knobs move automatically.
    library.applyPreset(row, ampState);
}

void PatchBrowser::changeListenerCallback(juce::ChangeBroadcaster*)
{
    listBox.updateContent();
    repaint();
}