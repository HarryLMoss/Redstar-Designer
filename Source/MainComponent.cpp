/*
    MainComponent.cpp
    Root component implementation.
*/

#include "MainComponent.h"

MainComponent::MainComponent()
{
    setSize(800, 500);
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff1a1a1a));

    g.setColour(juce::Colours::orange);
    g.setFont(28.0f);
    g.drawText("Redstar Designer",
               getLocalBounds().removeFromTop(60),
               juce::Justification::centred, false);

    g.setColour(juce::Colours::grey);
    g.setFont(14.0f);
    g.drawText("Amp control surface — work in progress",
               getLocalBounds(),
               juce::Justification::centred, false);
}

void MainComponent::resized()
{
    // Child component layout will go here in later commits
}