/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ParameterInterpolator.h"
#include "DelayEffect.h"

//==============================================================================
/**
*/
class AugsSynthAudioProcessor  : public AudioProcessor
{
public:
    float noteOnVel;
    AudioProcessorValueTreeState mParamTree;

    //==============================================================================
    AugsSynthAudioProcessor();
    ~AugsSynthAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    //==============================================================================
    void UpdateKeyState(MidiKeyboardState& newState);
private:
    void AddToAllChannels(float ValToAdd, int Sample, AudioSampleBuffer& buffer);
    void ApplyDistort(float& Sample, float& Inner, float& Outer);

    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    Synthesiser mSynth;
    MidiKeyboardState mKeyState;

    DelayEffect mDelay;

    ParameterInterpolator mIterpolator;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AugsSynthAudioProcessor)
};
