/*
    PresetLibrary.cpp
    Implementation of the preset collection.
*/

#include "PresetLibrary.h"
#include "PresetSerializer.h"

PresetLibrary::PresetLibrary()
{
    // Seed with one default preset so the browser isn't empty on launch.
    AmpState defaultState;
    addPreset("Default", defaultState);
}

juce::String PresetLibrary::getPresetName(int index) const
{
    return library.getChild(index).getProperty(IDs::presetName, "Untitled").toString();
}

void PresetLibrary::addPreset(const juce::String& name, const AmpState& state)
{
    juce::ValueTree preset(IDs::Preset);
    preset.setProperty(IDs::presetName, name, nullptr);

    // Copy each parameter value from the amp state into the preset.
    for (auto id : { IDs::gain, IDs::bass, IDs::mid, IDs::treble, IDs::master })
        preset.setProperty(id, state.get(id), nullptr);

    library.appendChild(preset, nullptr);
    sendChangeMessage();   // tells the UI to refresh
}

void PresetLibrary::applyPreset(int index, AmpState& state) const
{
    auto preset = library.getChild(index);
    if (! preset.isValid())
        return;

    for (auto id : { IDs::gain, IDs::bass, IDs::mid, IDs::treble, IDs::master })
        state.set(id, (float) preset.getProperty(id, 0.5f));
}

void PresetLibrary::addRandomPreset()
{
    auto& rng = juce::Random::getSystemRandom();

    juce::ValueTree preset(IDs::Preset);
    preset.setProperty(IDs::presetName,
                       "Random " + juce::String(rng.nextInt({ 1, 1000 })),
                       nullptr);

    // Constrained random: gain and master kept in sensible ranges so
    // randomised presets are usable, not extreme.
    preset.setProperty(IDs::gain,   rng.nextFloat() * 0.7f + 0.1f, nullptr);
    preset.setProperty(IDs::bass,   rng.nextFloat(),               nullptr);
    preset.setProperty(IDs::mid,    rng.nextFloat(),               nullptr);
    preset.setProperty(IDs::treble, rng.nextFloat(),               nullptr);
    preset.setProperty(IDs::master, rng.nextFloat() * 0.5f + 0.3f, nullptr);

    library.appendChild(preset, nullptr);
    sendChangeMessage();
}

void PresetLibrary::savePresetToFile(int index, const juce::File& file)
{
    if (index >= 0 && index < library.getNumChildren())
        PresetSerializer::savePreset(library.getChild(index), file);
}

bool PresetLibrary::loadPresetFromFile(const juce::File& file)
{
    auto loaded = PresetSerializer::loadPreset(file);
    if (! loaded.isValid())
        return false;

    library.appendChild(loaded, nullptr);
    sendChangeMessage();
    return true;
}