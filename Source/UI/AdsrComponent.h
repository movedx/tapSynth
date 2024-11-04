/*
  ==============================================================================

    AdsrComponent.h
    Created: 29 Oct 2024 2:26:59pm
    Author:  Bogdan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrComponent  : public juce::Component
{
public:
    AdsrComponent(juce::String name,
                  juce::AudioProcessorValueTreeState& apvts,
                  juce::String attackId, juce::String decayId,
                  juce::String sustainId, juce::String releaseId);

    ~AdsrComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;


private:
    void setSliderParams(juce::Slider& slider);

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    juce::String componentName;

    void setSliderWithLabel(juce::Slider& slider, 
                            juce::Label& label, 
                            juce::AudioProcessorValueTreeState& apvts, 
                            juce::String paramId, 
                            std::unique_ptr<SliderAttachment>& attachment);

    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;

    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    juce::ComboBox oscSelector;

    juce::Label attackLabel{ "Attack", "A" };
    juce::Label decayLabel{ "Decay", "D" };
    juce::Label sustainLabel{ "Sustain", "S" };
    juce::Label releaseLabel{ "Release", "R" };


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
