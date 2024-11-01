/*
  ==============================================================================

    OscComponent.h
    Created: 29 Oct 2024 6:39:04pm
    Author:  Bogdan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, juce::String fmFreqId, juce::String fmDepthId);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    void OscComponent::setSliderWithLabel(juce::Slider& slider,
                                          juce::Label& label,
                                          std::unique_ptr<SliderAttachment>& attachment,
                                          juce::AudioProcessorValueTreeState& apvts,
                                          juce::String paramId);

    juce::ComboBox oscWaveSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;

    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;

    std::unique_ptr<SliderAttachment> fmFreqAttachment;
    std::unique_ptr<SliderAttachment> fmDepthAttachment;


    juce::Label fmFreqLabel{"FM Freq", "FM Freq"};
    juce::Label fmDepthLabel{ "FM Depth", "FM Depth" };


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
