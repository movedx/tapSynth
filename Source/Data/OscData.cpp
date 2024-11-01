/*
  ==============================================================================

    OscData.cpp
    Created: 29 Oct 2024 5:52:03pm
    Author:  Bogdan

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec spec)
{
    fmOsc.prepare(spec);
    prepare(spec);
}

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
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + fmMod);
    lastMidiNote = midiNoteNumber;
}


void OscData::getNextAudioBlock(juce::dsp::ProcessContextReplacing<float>& context)
{
    for (int ch = 0; ch < context.getOutputBlock().getNumChannels(); ++ch)
    {
        for (int s = 0; s < context.getOutputBlock().getNumSamples(); ++s)
        {
            fmMod = fmOsc.processSample(context.getOutputBlock().getSample(ch, s)) * fmDepth;
        }
    }
    process(juce::dsp::ProcessContextReplacing<float>(context.getOutputBlock()));
}

void OscData::setFmParams(const float depth, const float freq)
{
    fmOsc.setFrequency(freq);
    fmDepth = depth;
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(lastMidiNote) + fmMod);
}
