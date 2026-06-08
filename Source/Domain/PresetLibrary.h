/*
    PresetLibrary.h
    Holds a collection of presets, each a snapshot of amp parameter values.
    Presets are stored as child nodes of one parent ValueTree.
    Broadcasts a change message whenever the collection changes so the UI
    (the PatchBrowser) can refresh.
*/

#pragma once

#include <JuceHeader.h>
#include "AmpState.h"
#include "../Identifiers.h"

class PresetLibrary : public juce::ChangeBroadcaster
{
public:
    PresetLibrary();

    int getNumPresets() const { return library.getNumChildren(); }
    juce::ValueTree getPreset(int index) const { return library.getChild(index); }
    juce::String getPresetName(int index) const;

    // Capture the current amp state as a new named preset.
    void addPreset(const juce::String& name, const AmpState& state);

    // Apply a stored preset's values back into the amp state.
    void applyPreset(int index, AmpState& state) const;

    // Generate a preset with constrained random values.
    void addRandomPreset();

    juce::ValueTree& getTree() { return library; }

private:
    juce::ValueTree library { IDs::Library };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetLibrary)
};