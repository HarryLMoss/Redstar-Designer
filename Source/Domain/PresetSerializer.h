/*
    PresetSerializer.h
    Saves and loads presets to/from disk as XML.

    Two reliability features worth noting:
      - Schema version field: every file records the format version, so
        future versions can migrate old files instead of breaking on them.
      - Atomic write: writes to a temp file then renames, so a crash mid-save
        can never leave a half-written, corrupted preset file.
*/

#pragma once

#include <JuceHeader.h>

class PresetSerializer
{
public:
    static constexpr int kSchemaVersion = 1;

    static bool savePreset(const juce::ValueTree& preset, const juce::File& destination);
    static juce::ValueTree loadPreset(const juce::File& source);
};