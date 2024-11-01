/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TapSynthAudioProcessorEditor::TapSynthAudioProcessorEditor (TapSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), adsr (audioProcessor.apvts), osc (audioProcessor.apvts, "OSC1WAVETYPE", "OSC1FMFREQ", "OSC1FMDEPTH")
{
    setSize (400, 300);
    addAndMakeVisible(osc);
    addAndMakeVisible(adsr);
}

TapSynthAudioProcessorEditor::~TapSynthAudioProcessorEditor()
{
}

//==============================================================================
void TapSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::black);
}

void TapSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    osc.setBounds(10, 10, 180, 200);
    adsr.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
}