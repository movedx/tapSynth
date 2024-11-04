/*
  ==============================================================================

    FilterComponent.h
    Created: 1 Nov 2024 11:53:29pm
    Author:  Bogdan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts,
                    juce::String filterTypeParamId,
                    juce::String filterFreqParamId,
                    juce::String filterResonanceParamId);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    void FilterComponent::setSliderWithLabel(juce::Slider& slider,
                                          juce::Label& label,
                                          std::unique_ptr<SliderAttachment>& attachment,
                                          juce::AudioProcessorValueTreeState& apvts,
                                          juce::String paramId);

    juce::ComboBox filterTypeSelector{ "Filter Type" };

    juce::Slider filterFreqSlider;
    juce::Slider filterResSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeSelectorAttachment;

    std::unique_ptr<SliderAttachment> filterFreqAttachment;
    std::unique_ptr<SliderAttachment> filterResAttachment;

    juce::Label filterTypeLabel{ "Filter Type", "Type" };
    juce::Label filterFreqLabel{ "Filter Freq", "Freq" };
    juce::Label filterResLabel{ "Filter Res", "Res" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
