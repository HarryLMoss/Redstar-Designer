#include "MainComponent.h"

MainComponent::MainComponent()
{
    addAndMakeVisible(parameterPanel);
    setSize(800, 500);
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff1a1a1a));

    g.setColour(juce::Colours::orange);
    g.setFont(24.0f);
    g.drawText("Redstar Designer",
               getLocalBounds().removeFromTop(50),
               juce::Justification::centred, false);
}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    area.removeFromTop(50); // leave room for the title

    // The parameter panel sits in the top portion of the window.
    parameterPanel.setBounds(area.removeFromTop(160));
}