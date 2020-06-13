/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AugsSynthAudioProcessorEditor::AugsSynthAudioProcessorEditor(AugsSynthAudioProcessor& p, MidiKeyboardState& keyState)
    : AudioProcessorEditor(&p), processor(p), keyboardComponent(keyState, MidiKeyboardComponent::horizontalKeyboard), mKeyState(keyState)

{
    //GUI
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (900, 700);
    InitGUI();
}

AugsSynthAudioProcessorEditor::~AugsSynthAudioProcessorEditor()
{
}

void AugsSynthAudioProcessorEditor::InitGUI()
{
    //Add on-screen keyboard
    addAndMakeVisible(keyboardComponent);
    mKeyState.addListener(this);//add listener

    //
    //Add Envelope Sliders
    InitSlider(AttackSlider, 10.0, 5000.0, 1.0);
    AtkSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParamTree, ATTACK_ID, AttackSlider);

    InitSlider(DecaySlider, 10.0, 5000.0, 1.0);
    DecaySliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParamTree, DECAY_ID, DecaySlider);

    InitSlider(SustainSlider, 0.0, 1.0, 0.01);
    SusSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParamTree, SUS_ID, SustainSlider);

    InitSlider(ReleaseSlider, 10.0, 5000.0, 1.0);
    RelSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParamTree, REL_ID, ReleaseSlider);
}

void AugsSynthAudioProcessorEditor::InitSlider(Slider& MySlider, double Min, double Max, double Increment)
{
    addAndMakeVisible(MySlider);
    MySlider.setRange(Min, Max, Increment); 
    MySlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    MySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
}

//==============================================================================
void AugsSynthAudioProcessorEditor::paint (Graphics& g)
{
    // fill the whole window white
    g.fillAll(Colour(30,30,30));

    // set the font size and draw text to the screen
    g.setFont(15.0f);


    g.setColour(Colours::darkgrey);
    g.drawRect(0, 0, 195, 120);
    g.setColour(Colours::wheat);
    g.drawSingleLineText("Osc Envelope", GUI_SPACING, GUI_SPACING);
    g.drawSingleLineText("A", GUI_SPACING+4, GUI_SPACING*2+4);
    g.drawSingleLineText("D", GUI_SPACING + 4, GUI_SPACING * 3 + 4);
    g.drawSingleLineText("S", GUI_SPACING + 4, GUI_SPACING * 4 + 4);
    g.drawSingleLineText("R", GUI_SPACING + 4, GUI_SPACING * 5 + 4);
}

void AugsSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // sets the position and size of the slider with arguments (x, y, width, height)
    int KeyHeight = 100;
    keyboardComponent.setBounds(GUI_SPACING, getHeight()- GUI_SPACING- KeyHeight, getWidth() - GUI_SPACING*2, KeyHeight);

    int SliderWidth = (int)(getWidth() / 6);
    AttackSlider.setBounds(2*GUI_SPACING, GUI_SPACING+10, SliderWidth, GUI_SPACING);
    DecaySlider.setBounds(2 * GUI_SPACING, GUI_SPACING*2 + 10, SliderWidth, GUI_SPACING);
    SustainSlider.setBounds(2 * GUI_SPACING, GUI_SPACING*3 + 10, SliderWidth, GUI_SPACING);
    ReleaseSlider.setBounds(2 * GUI_SPACING, GUI_SPACING*4 + 10, SliderWidth, GUI_SPACING);
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
