/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Defs.h"

#define GUI_SPACING 20
#define SLIDER_TXT_WIDTH (int)(GUI_SPACING*2.75)
#define SLIDER_TXT_HEIGHT 19

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
    void InitGUI();
    void InitSlider(Slider& MySlider, double Min, double Max, double Increment = 0.0);

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AugsSynthAudioProcessor& processor;

    //MidiKeyboard
    MidiKeyboardState& mKeyState;
    MidiKeyboardComponent keyboardComponent;

    //Env Sliders
    Slider AttackSlider;
    Slider DecaySlider;
    Slider SustainSlider;
    Slider ReleaseSlider;
public:
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> AtkSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> DecaySliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> SusSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> RelSliderAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AugsSynthAudioProcessorEditor)
};
