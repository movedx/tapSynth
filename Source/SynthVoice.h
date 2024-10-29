/*
  ==============================================================================

    SynthVoice.h
    Created: 24 Oct 2024 5:51:57pm
    Author:  Bogdan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/AdsrData.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
	bool canPlaySound(juce::SynthesiserSound*) override;
	void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
	void stopNote(float velocity, bool allowTailOff) override;
	void pitchWheelMoved(int newPitchWheelValue) override;
	void controllerMoved(int controllerNumber, int newControllerValue) override;
	void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
	void SynthVoice::update(const float attack, const float decay, const float sustain, const float release);
	void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

private:
	juce::AudioBuffer<float> synthBuffer;
	AdsrData adsr;
	// return std::sin(x); // sine wave
	// return x / juce::MathConstants<float>::pi; // saw wave
	// return x < 0.0f ? -1.0f : 1.0f; // square wave
	juce::dsp::Oscillator<float> osc{ [](float x) { return x / juce::MathConstants<float>::pi; } };
	juce::dsp::Gain<float> gain;
	bool isPrepared{ false };
};