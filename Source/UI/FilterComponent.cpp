/*
  ==============================================================================

    FilterComponent.cpp
    Created: 1 Nov 2024 11:53:29pm
    Author:  Bogdan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts,
                                 juce::String filterTypeParamId,
                                 juce::String filterFreqParamId, 
                                 juce::String filterResParamId)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    juce::StringArray choices{ "Lowpass", "Bandpass", "Highpass" };
    filterTypeSelector.addItemList(choices, 1);
    addAndMakeVisible(filterTypeSelector);

    filterTypeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, 
                                                                                                            filterTypeParamId, 
                                                                                                            filterTypeSelector);

    filterTypeLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    filterTypeLabel.setFont(15.0f);
    filterTypeLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(filterTypeLabel);

    setSliderWithLabel(filterFreqSlider, filterFreqLabel, filterFreqAttachment, apvts, filterFreqParamId);
    setSliderWithLabel(filterResSlider, filterResLabel, filterResAttachment, apvts, filterResParamId);

}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("Filter", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void FilterComponent::resized()
{
    const auto startY = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    filterTypeSelector.setBounds(10, startY + 5, 90, 30);
    filterTypeLabel.setBounds(10, startY - labelYOffset, 90, labelHeight);

    filterFreqSlider.setBounds(filterTypeSelector.getRight(), startY, sliderWidth, sliderHeight);
    filterFreqLabel.setBounds(filterFreqSlider.getX(), filterFreqSlider.getY() - labelYOffset, filterFreqSlider.getWidth(), labelHeight);

    filterResSlider.setBounds(filterFreqSlider.getRight(), startY, sliderWidth, sliderHeight);
    filterResLabel.setBounds(filterResSlider.getX(), filterResSlider.getY() - labelYOffset, filterResSlider.getWidth(), labelHeight);
}

void FilterComponent::setSliderWithLabel(juce::Slider& slider, 
                                         juce::Label& label, 
                                         std::unique_ptr<SliderAttachment>& attachment, 
                                         juce::AudioProcessorValueTreeState& apvts, 
                                         juce::String paramId)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);

    attachment = std::make_unique<SliderAttachment>(apvts, paramId, slider);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}
