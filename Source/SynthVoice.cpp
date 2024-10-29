/*
  ==============================================================================

	SynthVoice.cpp
	Created: 24 Oct 2024 5:51:57pm
	Author:  Bogdan

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
	return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound,
	int currentPitchWheelPosition)
{
	osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
	adsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
	adsr.noteOff();

	if (!allowTailOff || !adsr.isActive())
	{
		clearCurrentNote();
	}
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
	adsr.setSampleRate(sampleRate);

	juce::dsp::ProcessSpec spec;
	spec.maximumBlockSize = samplesPerBlock;
	spec.sampleRate = sampleRate;
	spec.numChannels = outputChannels;

	osc.prepare(spec);
	gain.prepare(spec);

	gain.setGainLinear(0.1f);



	isPrepared = true;
}

void SynthVoice::update(const float attack, const float decay, const float sustain, const float release)
{
	adsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
	jassert(isPrepared);

	//if (!isVoiceActive())
	//{
	//	return;
	//}

	//synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
	//synthBuffer.clear();


	//juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
	//osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
	//gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

	//adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

	//for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
	//{
	//	outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

	//	if (!adsr.isActive())
	//	{
	//		clearCurrentNote();
	//	}
	//}

	// This same issue can be solved in a different, more efficient way.
	// Using the AudioBlock::getSubBlock() method, we can get just a portion of our audiobuffer 
	// to pass into the oscillator's process() method. This way, we don't need to allocate 
	// and copy from a whole other AudioBuffer(SynthBuffer in this case).My SynthVoice.cpp's renderNextBlock() method is the following:

	//Method 2:===========================================================================================================

	if (!isVoiceActive()) return;



	auto audioBlock = juce::dsp::AudioBlock<float>(outputBuffer).getSubBlock(startSample, numSamples);
	
	//juce::dsp::AudioBlock<float> audioBlock{ outputBuffer, (size_t)startSample }; // even simpler but still click on note end:

	juce::dsp::ProcessContextReplacing<float> context(audioBlock);

	osc.process(context);
	gain.process(context);

	adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);

	if (!adsr.isActive())
	{
		clearCurrentNote();
	}
	// Method 3: see synthesiser demo

}
