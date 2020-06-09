/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AugsSynthAudioProcessorEditor::AugsSynthAudioProcessorEditor (AugsSynthAudioProcessor& p, MidiKeyboardState& keyState)
    : AudioProcessorEditor (&p), processor (p), keyboardComponent(keyState, MidiKeyboardComponent::horizontalKeyboard), mKeyState(keyState)

{
    //GUI
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);

    //Add on-screen keyboard
    addAndMakeVisible(keyboardComponent);

    //=====================

    mKeyState.addListener(this);
}

AugsSynthAudioProcessorEditor::~AugsSynthAudioProcessorEditor()
{
}



//==============================================================================
void AugsSynthAudioProcessorEditor::paint (Graphics& g)
{
    // fill the whole window white
    g.fillAll(Colours::white);

    // set the current drawing colour to black
    g.setColour(Colours::black);

    // set the font size and draw text to the screen
    g.setFont(15.0f);

    g.drawFittedText("Midi Volume", 0, 0, getWidth(), 30, Justification::centred, 1);
}

void AugsSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // sets the position and size of the slider with arguments (x, y, width, height)
    int KeyHeight = (int)(getHeight() / 5);
    keyboardComponent.setBounds(GUI_SPACING, getHeight()- GUI_SPACING- KeyHeight, getWidth() - GUI_SPACING*2, KeyHeight);
}

void AugsSynthAudioProcessorEditor::handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) 
{
    auto m = MidiMessage::noteOn(midiChannel, midiNoteNumber, velocity);
    m.setTimeStamp(Time::getMillisecondCounterHiRes() * 0.001);
}

void AugsSynthAudioProcessorEditor::handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber,float /*velocity*/) 
{
    auto m = MidiMessage::noteOff(midiChannel, midiNoteNumber);
    m.setTimeStamp(Time::getMillisecondCounterHiRes() * 0.001);
}
