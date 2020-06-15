/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "AugsVoice.h"

//==============================================================================
AugsSynthAudioProcessor::AugsSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), mParamTree(*this, nullptr, "PARAMS", createParameterLayout())
#endif
{
    for (auto i = 0; i < 8; ++i)                // Define voices
        mSynth.addVoice(new AugsVoice());

    mSynth.addSound(new AugsSound());       // Add Sound
}

AugsSynthAudioProcessor::~AugsSynthAudioProcessor()
{
}

AudioProcessorValueTreeState::ParameterLayout AugsSynthAudioProcessor::createParameterLayout()
{
 /*   std::vector<std::unique_ptr<AudioParameterParameter>> params;

    params.push_back(std::make_unique<AudioParameterFloat>();

    return { params.begin(), params.end() };*/
    AudioProcessorValueTreeState::ParameterLayout layout;
    for (int i = 0; i < NUM_FLOAT_PARAMS; i++)//add float parameters
    {
        NormalisableRange<float> Range = NormalisableRange<float>(FloatParamProps[i].minVal, FloatParamProps[i].maxVal);
        Range.skew = FloatParamProps[i].skewFactor;
        layout.add(std::make_unique<AudioParameterFloat>(FloatParamProps[i].ID, FloatParamProps[i].Name, Range, FloatParamProps[i].defaultVal));
    }

    return layout;
}

//==============================================================================
const String AugsSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AugsSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AugsSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AugsSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AugsSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AugsSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AugsSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AugsSynthAudioProcessor::setCurrentProgram (int index)
{
}

const String AugsSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void AugsSynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void AugsSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    mSynth.setCurrentPlaybackSampleRate(sampleRate);
}

void AugsSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AugsSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void AugsSynthAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    buffer.clear();
    mKeyState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);

    double Attack = mParamTree.getParameterAsValue(FloatParamProps[0].ID).getValue();
    double Decay = mParamTree.getParameterAsValue(FloatParamProps[1].ID).getValue();
    double Sustain = mParamTree.getParameterAsValue(FloatParamProps[2].ID).getValue();
    double Release = mParamTree.getParameterAsValue(FloatParamProps[3].ID).getValue();
    int OscMode = mParamTree.getParameterAsValue(FloatParamProps[5].ID).getValue();
    int FilterMode = mParamTree.getParameterAsValue(FloatParamProps[8].ID).getValue();
    double FilterCut = mParamTree.getParameterAsValue(FloatParamProps[9].ID).getValue();
    double FilterRes = mParamTree.getParameterAsValue(FloatParamProps[10].ID).getValue();

    for (int i = 0; i < mSynth.getNumVoices(); i++)
    {
        auto* Voice = dynamic_cast<AugsVoice*>(mSynth.getVoice(i));
        if (Voice)
        {
            Voice->setEnvelope(Attack, Decay, Sustain, Release);
            Voice->setOsc(static_cast<Oscillator::OscillatorMode>(OscMode));
            Voice->setFilter(FilterCut, FilterRes, FilterMode);
        }
    }

    mSynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    float PowDist = (float)mParamTree.getParameterAsValue(FloatParamProps[6].ID).getValue();
    float TrimDist = 1-(float)mParamTree.getParameterAsValue(FloatParamProps[7].ID).getValue();
    double Volume = mParamTree.getParameterAsValue(FloatParamProps[4].ID).getValue();

    for (int sample = 0; sample < buffer.getNumSamples(); sample++)
    {
        for (int channel = 0; channel < buffer.getNumChannels(); channel++)
        {
            float MySample = buffer.getSample(channel, sample);

            ApplyDistort(MySample, PowDist, TrimDist);

            MySample *= Volume;
            buffer.setSample(channel, sample, MySample);
        }
    }
}

void AugsSynthAudioProcessor::ApplyDistort(float& Sample, float& Power, float& Trim)
{
    //Apply Power
    if (Sample >= 0.0f)
    {
        Sample = pow(Sample, Power);
    }
    else if (Sample < 0.0)
    {
        Sample = -pow(-Sample, Power);
    }



    //Apply Outer
    if (Sample > Trim)
    {
        Sample = Trim;
    }
    else if (Sample < -Trim)
    {
        Sample = -Trim;
    }

    Sample /= Trim;

}


//==============================================================================
bool AugsSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* AugsSynthAudioProcessor::createEditor()
{
    return new AugsSynthAudioProcessorEditor (*this, mKeyState);
}

//==============================================================================
void AugsSynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void AugsSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AugsSynthAudioProcessor();
}