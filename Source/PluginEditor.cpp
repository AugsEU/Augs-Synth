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
    InitSlider(AttackSlider, 0);                //A
    AttackSlider.Slider.setTextValueSuffix("s");
    InitSlider(DecaySlider, 1);                 //D
    DecaySlider.Slider.setTextValueSuffix("s");
    InitSlider(SustainSlider, 2);               //S
    InitSlider(ReleaseSlider, 3);               //R
    ReleaseSlider.Slider.setTextValueSuffix("s");

    //
    //Volume slider
    InitSlider(VolumeSlider, 4, 0.01, Slider::SliderStyle::LinearVertical);
    VolumeSlider.Slider.setPopupDisplayEnabled(false, false, nullptr);

    //
    //Osc selection
    InitCombo(OscSelect, 5, { "Sine","Saw","Square","Triangle" });

    //distortion
    InitSlider(PowerDistortionSlider, 6);
    InitSlider(TrimDistortionSlider, 7);

    //Filter
    InitCombo(FilterSelect, 8, {"Off","Low pass", "High pass", "Band pass", "Band reject" });
    InitSlider(CutOffSlider, 9);
    CutOffSlider.Slider.setTextValueSuffix("Hz");
    InitSlider(ResonanceSlider, 10);
    InitCombo(LowTypeSelect, 14, { "Single pole" , "3rd Order" });
    InitCombo(BandTypeSelect, 15, { "3rd Order" });

    //Delay
    InitSlider(DlyVolumeSlider, 11);
    InitSlider(DlyFallOffSlider, 12);
    InitSlider(DlyTimeSlider, 13);
    DlyTimeSlider.Slider.setTextValueSuffix("s");

    //Tuning
    InitCombo(TuningSelect, 16, { "12-TET","7-12-ET", "4-12-ET","Exact-ET","Tri ET" });
}

void AugsSynthAudioProcessorEditor::InitSlider(Slider_Attach& MySlider, int Param_ID, double Increment, Slider::SliderStyle style)
{
    addAndMakeVisible(MySlider.Slider);
    MySlider.Slider.setRange(FloatParamProps[Param_ID].minVal, FloatParamProps[Param_ID].maxVal, Increment);
    MySlider.Slider.setSliderStyle(style);
    MySlider.Slider.setPopupDisplayEnabled(true, true, nullptr);
    MySlider.Slider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    MySlider.Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParamTree, FloatParamProps[Param_ID].ID, MySlider.Slider);
}

void AugsSynthAudioProcessorEditor::InitCombo(Combo_Attach& MyCombo, int Param_ID, const StringArray& items)
{
    addAndMakeVisible(MyCombo.ComboBox);
    MyCombo.ComboBox.addItemList(items,1);
    MyCombo.Attachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.mParamTree, FloatParamProps[Param_ID].ID, MyCombo.ComboBox);
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
    g.drawSingleLineText("Distortion", 14, GUI_SPACING * 1 + 472);
    g.drawSingleLineText("Pow", 14, GUI_SPACING * 2 + 473);
    g.drawSingleLineText("Trim", 14, GUI_SPACING * 3 + 473);

    //Tuning
    g.setColour(Colours::darkgrey);
    g.drawRect(0, 410, 195, 60);
    g.setColour(Colours::wheat);
    g.drawSingleLineText("Tuning", 14, GUI_SPACING * 1 + 412);

    //ADSR
    g.setColour(Colours::darkgrey);
    g.drawRect(340, 0, 195, 80);
    g.setColour(Colours::wheat);
    g.drawSingleLineText("Filter", 335 + GUI_SPACING, GUI_SPACING);
    g.drawSingleLineText("Cut", GUI_SPACING + 334, GUI_SPACING * 2 + 4);
    g.drawSingleLineText("Res", GUI_SPACING + 334, GUI_SPACING * 3 + 4);

    //Delay
    g.setColour(Colours::darkgrey);
    g.drawRect(195, 450, 210, 100);
    g.setColour(Colours::wheat);
    g.drawSingleLineText("Delay", 210, GUI_SPACING * 1 + 452);
    g.drawSingleLineText("Vol", 210, GUI_SPACING * 2 + 453);
    g.drawSingleLineText("Fall-off", 210, GUI_SPACING * 3 + 453);
    g.drawSingleLineText("Time", 210, GUI_SPACING * 4 + 453);

}

void AugsSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // sets the position and size of the slider with arguments (x, y, width, height)
    int KeyHeight = 100;
    keyboardComponent.setBounds(GUI_SPACING, getHeight()- GUI_SPACING- KeyHeight, getWidth() - GUI_SPACING*2, KeyHeight);

    int SliderWidth = (int)(getWidth() / 6);//ADSR Sliders
    AttackSlider.Slider.setBounds(2*GUI_SPACING, GUI_SPACING+10, SliderWidth, GUI_SPACING);
    DecaySlider.Slider.setBounds(2 * GUI_SPACING, GUI_SPACING*2 + 10, SliderWidth, GUI_SPACING);
    SustainSlider.Slider.setBounds(2 * GUI_SPACING, GUI_SPACING*3 + 10, SliderWidth, GUI_SPACING);
    ReleaseSlider.Slider.setBounds(2 * GUI_SPACING, GUI_SPACING*4 + 10, SliderWidth, GUI_SPACING);

    //Volume
    VolumeSlider.Slider.setBounds(190 + GUI_SPACING, 20, GUI_SPACING, 100);

    //Osc selector
    OscSelect.ComboBox.setBounds(245, 0, 95, 20);

    //distortion
    PowerDistortionSlider.Slider.setBounds(2 * GUI_SPACING, 500, SliderWidth, GUI_SPACING);
    TrimDistortionSlider.Slider.setBounds(2 * GUI_SPACING, 500 + GUI_SPACING, SliderWidth, GUI_SPACING);

    //Tuning
    TuningSelect.ComboBox.setBounds(10, 440, 95, 20);

    //Filter
    FilterSelect.ComboBox.setBounds(245, 21, 95, 20);
    LowTypeSelect.ComboBox.setBounds(245, 42, 95, 20);
    BandTypeSelect.ComboBox.setBounds(245, 63, 95, 20);
    CutOffSlider.Slider.setBounds(380, GUI_SPACING * 1 + 10, SliderWidth, GUI_SPACING);
    ResonanceSlider.Slider.setBounds(380, GUI_SPACING * 2 + 10, SliderWidth, GUI_SPACING);
    

    //Delay
    DlyVolumeSlider.Slider.setBounds(2 * GUI_SPACING + 215, 500 - GUI_SPACING, SliderWidth, GUI_SPACING);
    DlyFallOffSlider.Slider.setBounds(2 * GUI_SPACING + 215, 500 , SliderWidth, GUI_SPACING);
    DlyTimeSlider.Slider.setBounds(2 * GUI_SPACING + 215, 500 + GUI_SPACING, SliderWidth, GUI_SPACING);
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
