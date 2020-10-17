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

typedef struct
{
    Slider Slider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> Attachment;
} Slider_Attach;

typedef struct
{
    ComboBox ComboBox;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> Attachment;
} Combo_Attach;


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

    //UI Elements
    //Env Sliders
    Slider_Attach AttackSlider;
    Slider_Attach DecaySlider;
    Slider_Attach SustainSlider;
    Slider_Attach ReleaseSlider;

    //Volume Slider
    Slider_Attach VolumeSlider;

    //OscCombo
    Combo_Attach OscSelect;

    //Distortion
    Slider_Attach PowerDistortionSlider;
    Slider_Attach TrimDistortionSlider;

    //Filter settings
    Combo_Attach FilterSelect;
    Slider_Attach CutOffSlider;
    Slider_Attach ResonanceSlider;
    Combo_Attach LowTypeSelect;
    Combo_Attach BandTypeSelect;

    //Delay settings
    Slider_Attach DlyVolumeSlider;
    Slider_Attach DlyFallOffSlider;
    Slider_Attach DlyTimeSlider;

    //Tuning
    Combo_Attach TuningSelect;
    

private:
    void InitGUI();
    void InitSlider(Slider_Attach& MySlider, int Param_ID, double Increment = 0.0, Slider::SliderStyle style = Slider::SliderStyle::LinearHorizontal);
    void InitCombo(Combo_Attach& MyCombo, int Param_ID, const StringArray& items);

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AugsSynthAudioProcessor& processor;

    //MidiKeyboard
    MidiKeyboardState& mKeyState;
    MidiKeyboardComponent keyboardComponent;

public:


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AugsSynthAudioProcessorEditor)
};
