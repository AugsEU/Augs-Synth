/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#define GUI_SPACING 10

//==============================================================================
/**
*/
class AugsSynthAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    AugsSynthAudioProcessorEditor (AugsSynthAudioProcessor&);
    ~AugsSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AugsSynthAudioProcessor& processor;

    Slider midiVolume; // [1]
    MidiKeyboardState keyboardState;
    MidiKeyboardComponent keyboardComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AugsSynthAudioProcessorEditor)
};
