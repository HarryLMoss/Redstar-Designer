/*
    PatchBrowser.h
    Displays the preset library as a list, with buttons to save the current
    state as a new preset, randomise, and load the selected preset.

    Observes the PresetLibrary via ChangeListener so the list refreshes
    whenever presets are added.
*/

#pragma once

#include <JuceHeader.h>
#include "../Domain/PresetLibrary.h"
#include "../Domain/AmpState.h"

class PatchBrowser : public juce::Component,
                     public  juce::ListBoxModel,
                     private juce::ChangeListener
{
public:
    PatchBrowser(PresetLibrary& library, AmpState& state);
    ~PatchBrowser() override;

    void resized() override;

    // ListBoxModel
    int getNumRows() override;
    void paintListBoxItem(int row, juce::Graphics& g,
                          int width, int height, bool rowIsSelected) override;
    void listBoxItemClicked(int row, const juce::MouseEvent&) override;

private:
    void changeListenerCallback(juce::ChangeBroadcaster*) override;

    PresetLibrary& library;
    AmpState&      ampState;

    juce::ListBox    listBox;
    juce::TextButton saveButton   { "Save Current" };
    juce::TextButton randomButton { "Randomise" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PatchBrowser)
};