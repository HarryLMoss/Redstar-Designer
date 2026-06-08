/*
    PresetSerializer.cpp
    XML serialisation for presets, with versioning and atomic writes.
*/

#include "PresetSerializer.h"
#include "../Identifiers.h"

bool PresetSerializer::savePreset(const juce::ValueTree& preset,
                                  const juce::File& destination)
{
    // Tag the preset with the current schema version before saving.
    auto copy = preset.createCopy();
    copy.setProperty(IDs::schemaVer, kSchemaVersion, nullptr);

    auto xml = copy.createXml();
    if (xml == nullptr)
        return false;

    // Atomic write: write to a temp file, then rename over the target.
    auto temp = destination.withFileExtension(".tmp");
    if (! xml->writeTo(temp))
        return false;

    return temp.moveFileTo(destination);
}

juce::ValueTree PresetSerializer::loadPreset(const juce::File& source)
{
    if (! source.existsAsFile())
        return {};

    auto xml = juce::XmlDocument::parse(source);
    if (xml == nullptr)
        return {};

    auto tree = juce::ValueTree::fromXml(*xml);

    // Refuse to load files newer than we understand.
    int version = (int) tree.getProperty(IDs::schemaVer, 0);
    if (version > kSchemaVersion)
        return {};

    return tree;
}