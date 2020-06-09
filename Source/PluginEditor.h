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
class AugsSynthAudioProcessorEditor : public AudioProcessorEditor, public MidiKeyboardStateListener
{
public:
    AugsSynthAudioProcessorEditor (AugsSynthAudioProcessor& Processor, MidiKeyboardState& keyState);
    ~AugsSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    //MidiKeyboardStateListener
    void handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
    void handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AugsSynthAudioProcessor& processor;
    MidiKeyboardState& mKeyState;
    MidiKeyboardComponent keyboardComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AugsSynthAudioProcessorEditor)
};
