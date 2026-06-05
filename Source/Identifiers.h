/*
    Identifiers.h
    Centralised string identifiers for the amp state ValueTree.
    Defining these once prevents typos — a mistyped identifier becomes
    a compile error rather than a silent runtime bug.
*/

#pragma once

#include <JuceHeader.h>

namespace IDs
{
    // ValueTree node types
    inline const juce::Identifier AmpState  ("AmpState");
    inline const juce::Identifier Preset     ("Preset");
    inline const juce::Identifier Library    ("Library");

    // Amp parameter properties
    inline const juce::Identifier gain       ("gain");
    inline const juce::Identifier bass       ("bass");
    inline const juce::Identifier mid        ("mid");
    inline const juce::Identifier treble     ("treble");
    inline const juce::Identifier master     ("master");

    // Preset metadata
    inline const juce::Identifier presetName ("presetName");
    inline const juce::Identifier schemaVer  ("schemaVer");
}