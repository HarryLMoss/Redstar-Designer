/*
    MainComponent.h
    Root component of Redstar Designer.
    For now just paints a placeholder — UI is built up over subsequent commits.
*/

#pragma once

#include <JuceHeader.h>
#include "Domain/AmpState.h"

class MainComponent : public juce::Component
{
public:
    MainComponent();
    ~MainComponent() override = default;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    AmpState ampState;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};