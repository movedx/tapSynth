/*
  ==============================================================================

    OscData.h
    Created: 29 Oct 2024 5:52:03pm
    Author:  Bogdan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//enum OscWaveType {
//    SIN,
//    SAW,
//    SQUARE
//};

class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec spec) { prepare(spec); };
    void setWaveType(const int choice);
    void setWaveFrequency(const int midiNoteNumber);
    void getNextAudioBlock(juce::dsp::ProcessContextReplacing<float>& context);

private:
    juce::dsp::Oscillator<float> osc{ [](float x) { return x / juce::MathConstants<float>::pi; } };
};