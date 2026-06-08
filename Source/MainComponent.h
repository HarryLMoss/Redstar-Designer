/*
    MainComponent.h
    Root component of Redstar Designer.
    Holds the AmpState and PresetLibrary, and passes references to them.
*/

#pragma once

#include <JuceHeader.h>
#include "Domain/AmpState.h"
#include "Domain/PresetLibrary.h"
#include "UI/ParameterPanel.h"
#include "UI/PatchBrowser.h"

class MainComponent : public juce::Component
{
public:
    MainComponent();
    ~MainComponent() override = default;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    AmpState       ampState;
    PresetLibrary  presetLibrary;
    ParameterPanel parameterPanel { ampState };
    PatchBrowser   patchBrowser   { presetLibrary, ampState };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};