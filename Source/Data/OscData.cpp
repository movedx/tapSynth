/*
  ==============================================================================

    OscData.cpp
    Created: 29 Oct 2024 5:52:03pm
    Author:  Bogdan

  ==============================================================================
*/

#include "OscData.h"

void OscData::setWaveType(const int choice)
{
    switch (choice) {
    case 0:
        initialise([](float x) { return std::sin(x); }); // sine wave
        break;
    case 1:
        initialise([](float x) { return x / juce::MathConstants<float>::pi; }); // saw wave
        break;
    case 2:
        initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f; }); // square wave
        break;
    default:
        jassertfalse;
        break;
    }
}

void OscData::setWaveFrequency(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
}


void OscData::getNextAudioBlock(juce::dsp::ProcessContextReplacing<float>& context)
{
    process(context);
}
