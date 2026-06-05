/*
    AmpState.cpp
    Implementation of the amp parameter state model.
*/

#include "AmpState.h"

AmpState::AmpState()
{
    resetToDefault();
}

float AmpState::get(const juce::Identifier& param) const
{
    return (float) state.getProperty(param, 0.5f);
}

void AmpState::set(const juce::Identifier& param, float value)
{
    // nullptr = no UndoManager for now. Listeners are notified automatically.
    state.setProperty(param, value, nullptr);
}

void AmpState::resetToDefault()
{
    state.setProperty(IDs::gain,   0.5f, nullptr);
    state.setProperty(IDs::bass,   0.5f, nullptr);
    state.setProperty(IDs::mid,    0.5f, nullptr);
    state.setProperty(IDs::treble, 0.5f, nullptr);
    state.setProperty(IDs::master, 0.5f, nullptr);
}