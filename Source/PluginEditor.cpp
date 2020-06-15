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
    getLookAndFeel().setColour(Slider::trackColourId, Colours::wheat);

    //Add on-screen keyboard
    addAndMakeVisible(keyboardComponent);
    mKeyState.addListener(this);//add listener

    //
    //Add Envelope Sliders
    InitSlider(AttackSlider, FloatParamProps[0].minVal, FloatParamProps[0].maxVal, 0.01);
    AttackSlider.setTextValueSuffix("s");
    AtkSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParamTree, FloatParamProps[0].ID, AttackSlider);

    InitSlider(DecaySlider, FloatParamProps[1].minVal, FloatParamProps[1].maxVal, 1.0);
    DecaySlider.setTextValueSuffix("s");
    DecaySliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParamTree, FloatParamProps[1].ID, DecaySlider);

    InitSlider(SustainSlider, FloatParamProps[2].minVal, FloatParamProps[2].maxVal, 0.01);
    SusSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParamTree, FloatParamProps[2].ID, SustainSlider);

    InitSlider(ReleaseSlider, FloatParamProps[3].minVal, FloatParamProps[3].maxVal, 0.01);
    ReleaseSlider.setTextValueSuffix("s");
    RelSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParamTree, FloatParamProps[3].ID, ReleaseSlider);

    //
    //Volume slider
    InitSlider(VolumeSlider, FloatParamProps[4].minVal, FloatParamProps[4].maxVal, 0.01, Slider::SliderStyle::LinearVertical);
    VolumeSlider.setPopupDisplayEnabled(false, false, nullptr);
    VolSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParamTree, FloatParamProps[4].ID, VolumeSlider);

    //
    //Osc selection
    addAndMakeVisible(OscSelect);
    OscSelect.addItemList({ "Sine","Saw","Square","Triangle" }, 1);
    OscSelectAttach = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.mParamTree, FloatParamProps[5].ID, OscSelect);

    //distortion
    InitSlider(PowerDistortionSlider, FloatParamProps[6].minVal, FloatParamProps[6].maxVal);
    PowDistortAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParamTree, FloatParamProps[6].ID, PowerDistortionSlider);

    InitSlider(TrimDistortionSlider, FloatParamProps[7].minVal, FloatParamProps[7].maxVal);
    TrimDistortAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParamTree, FloatParamProps[7].ID, TrimDistortionSlider);

    //Filter
    addAndMakeVisible(FilterSelect);
    FilterSelect.addItemList({ "Low pass", "High pass", "Band pass", "Off" }, 1);
    FilterSelectAttach = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.mParamTree, FloatParamProps[8].ID, FilterSelect);

    InitSlider(CutOffSlider, FloatParamProps[9].minVal, FloatParamProps[9].maxVal);
    CutOffAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParamTree, FloatParamProps[9].ID, CutOffSlider);

    InitSlider(ResonanceSlider, FloatParamProps[10].minVal, FloatParamProps[10].maxVal);
    ResAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParamTree, FloatParamProps[10].ID, ResonanceSlider);

}

void AugsSynthAudioProcessorEditor::InitSlider(Slider& MySlider, double Min, double Max, double Increment, Slider::SliderStyle style)
{
    addAndMakeVisible(MySlider);
    MySlider.setRange(Min, Max, Increment); 
    MySlider.setSliderStyle(style);
    MySlider.setPopupDisplayEnabled(true, true, nullptr);
    MySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
}

//==============================================================================
void AugsSynthAudioProcessorEditor::paint (Graphics& g)
{
    // fill the whole window white
    g.fillAll(Colour(30,30,30));

    // set the font size and draw text to the screen
    g.setFont(15.0f);

    //ADSR
    g.setColour(Colours::darkgrey);
    g.drawRect(0, 0, 195, 120);
    g.setColour(Colours::wheat);
    g.drawSingleLineText("Osc Envelope", GUI_SPACING, GUI_SPACING);
    g.drawSingleLineText("A", GUI_SPACING+4, GUI_SPACING*2+4);
    g.drawSingleLineText("D", GUI_SPACING + 4, GUI_SPACING * 3 + 4);
    g.drawSingleLineText("S", GUI_SPACING + 4, GUI_SPACING * 4 + 4);
    g.drawSingleLineText("R", GUI_SPACING + 4, GUI_SPACING * 5 + 4);

    //Volume
    g.setColour(Colours::darkgrey);
    g.drawRect(195, 0, 50, 120);
    g.setColour(Colours::wheat);
    g.drawSingleLineText("Vol", 15 + 195, GUI_SPACING);

    //Distortion
    g.setColour(Colours::darkgrey);
    g.drawRect(0, 470, 195, 80);
    g.setColour(Colours::wheat);
    g.drawSingleLineText("Distortion", 17, GUI_SPACING * 1 + 472);
    g.drawSingleLineText("Pow", 17, GUI_SPACING * 2 + 473);
    g.drawSingleLineText("Trim", 17, GUI_SPACING * 3 + 473);

    //ADSR
    g.setColour(Colours::darkgrey);
    g.drawRect(340, 0, 195, 80);
    g.setColour(Colours::wheat);
    g.drawSingleLineText("Filter", 335 + GUI_SPACING, GUI_SPACING);
    g.drawSingleLineText("Cut", GUI_SPACING + 334, GUI_SPACING * 2 + 4);
    g.drawSingleLineText("Res", GUI_SPACING + 334, GUI_SPACING * 3 + 4);

}

void AugsSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // sets the position and size of the slider with arguments (x, y, width, height)
    int KeyHeight = 100;
    keyboardComponent.setBounds(GUI_SPACING, getHeight()- GUI_SPACING- KeyHeight, getWidth() - GUI_SPACING*2, KeyHeight);

    int SliderWidth = (int)(getWidth() / 6);//ADSR Sliders
    AttackSlider.setBounds(2*GUI_SPACING, GUI_SPACING+10, SliderWidth, GUI_SPACING);
    DecaySlider.setBounds(2 * GUI_SPACING, GUI_SPACING*2 + 10, SliderWidth, GUI_SPACING);
    SustainSlider.setBounds(2 * GUI_SPACING, GUI_SPACING*3 + 10, SliderWidth, GUI_SPACING);
    ReleaseSlider.setBounds(2 * GUI_SPACING, GUI_SPACING*4 + 10, SliderWidth, GUI_SPACING);

    //Volume
    VolumeSlider.setBounds(190 + GUI_SPACING, 20, GUI_SPACING, 100);

    //Osc selector
    OscSelect.setBounds(245, 0, 95, 20);

    //distortion
    PowerDistortionSlider.setBounds(2 * GUI_SPACING, 500, SliderWidth, GUI_SPACING);
    TrimDistortionSlider.setBounds(2 * GUI_SPACING, 500 + GUI_SPACING, SliderWidth, GUI_SPACING);

    //Filter
    FilterSelect.setBounds(245, 21, 95, 20);
    CutOffSlider.setBounds(380, GUI_SPACING * 1 + 10, SliderWidth, GUI_SPACING);
    ResonanceSlider.setBounds(380, GUI_SPACING * 2 + 10, SliderWidth, GUI_SPACING);
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
