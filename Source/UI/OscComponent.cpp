/*
  ==============================================================================

    OscComponent.cpp
    Created: 29 Oct 2024 6:39:04pm
    Author:  Bogdan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    juce::StringArray choices { "Sine", "Saw", "Square"};
    oscWaveSelector.addItemList(choices, 1);
    addAndMakeVisible(oscWaveSelector);

    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorId, oscWaveSelector);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(juce::Colours::black);
}

void OscComponent::resized()
{
    oscWaveSelector.setBounds(0, 0, 90, 20);
}
