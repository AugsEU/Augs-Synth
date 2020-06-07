/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AugsSynthAudioProcessorEditor::AugsSynthAudioProcessorEditor (AugsSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), keyboardComponent(keyboardState, MidiKeyboardComponent::horizontalKeyboard)

{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);


    
    addAndMakeVisible(keyboardComponent);
    //setAudioChannels(0, 2);

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
