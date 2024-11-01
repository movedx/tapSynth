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
    void prepareToPlay(juce::dsp::ProcessSpec spec);
    void setWaveType(const int choice);
    void setWaveFrequency(const int midiNoteNumber);
    void getNextAudioBlock(juce::dsp::ProcessContextReplacing<float>& context);
    void setFmParams(const float depth, const float freq);

private:
    juce::dsp::Oscillator<float> fmOsc { [](float x) { return std::sin(x); } };
    float fmMod{ 0.0f };
    float fmDepth{ 0.0f };
    int lastMidiNote{ 0 };
};