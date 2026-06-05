/*
    AmpState.h
    Wraps the amp parameter ValueTree and provides safe typed access.
    This is the single source of truth for the current amp settings.
    The UI observes it; presets read from and write to it.
*/

#pragma once

#include <JuceHeader.h>
#include "../Identifiers.h"

class AmpState
{
public:
    AmpState();

    // Access to the underlying tree (for listeners and serialisation)
    juce::ValueTree& getTree() { return state; }

    // Typed getters/setters for each parameter (0.0–1.0 range)
    float get(const juce::Identifier& param) const;
    void  set(const juce::Identifier& param, float value);

    // Reset all parameters to sensible defaults
    void resetToDefault();

private:
    juce::ValueTree state { IDs::AmpState };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AmpState)
};