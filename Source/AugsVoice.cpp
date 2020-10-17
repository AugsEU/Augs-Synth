#include "AugsVoice.h"

bool AugsVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast<AugsSound*> (sound) != nullptr;
}

void AugsVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound*, int /*currentPitchWheelPosition*/)
{
    mVelocity = velocity;
    TuningType NoteTuningType = static_cast<TuningType>((int)rInterpolator.GetFloatOld(16));
    mOsc.setFrequency(NoteNumberToHz(midiNoteNumber, NoteTuningType));
    mEnv.enterStage(EnvelopeGenerator::EnvelopeStage::ENVELOPE_STAGE_ATTACK);
}

double AugsVoice::NoteNumberToHz(int midiNoteNumber, TuningType TT)
{
    switch (TT)
    {
    case AugsVoice::TWELVE_TET:
        return FREQ_A * std::pow(2.0, (midiNoteNumber - 69) / 12.0);
    case AugsVoice::SEVEN_TWELVE_ET:
        return FREQ_A * std::pow(1.5, (midiNoteNumber - 69) / 7.0);
    case AugsVoice::FOUR_TWELVE_ET:
        return FREQ_A * std::pow(1.25, (midiNoteNumber - 69) / 4.0);
    default:
        return 440.0f;
    }
}

void AugsVoice::setEnvelope(double a, double d, double s, double r)
{
    mEnv.setStageValue(EnvelopeGenerator::EnvelopeStage::ENVELOPE_STAGE_ATTACK, a);
    mEnv.setStageValue(EnvelopeGenerator::EnvelopeStage::ENVELOPE_STAGE_DECAY, d);
    mEnv.setStageValue(EnvelopeGenerator::EnvelopeStage::ENVELOPE_STAGE_SUSTAIN, s);
    mEnv.setStageValue(EnvelopeGenerator::EnvelopeStage::ENVELOPE_STAGE_RELEASE, r);
}

void AugsVoice::stopNote(float /*velocity*/, bool allowTailOff)
{

    if (!allowTailOff)
    {
        clearCurrentNote();
        mEnv.enterStage(EnvelopeGenerator::EnvelopeStage::ENVELOPE_STAGE_OFF);
    }
    else
    {
        mEnv.enterStage(EnvelopeGenerator::EnvelopeStage::ENVELOPE_STAGE_RELEASE);
    }
    
}


void AugsVoice::pitchWheelMoved(int newPitchWheelValue) {}

void AugsVoice::controllerMoved(int controllerNumber, int newControllerValue) {}

void AugsVoice::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{

    for (int sample = 0; sample < numSamples; sample++)
    {
        double Attack = rInterpolator.GetFloat(0, sample);
        double Decay = rInterpolator.GetFloat(1, sample);
        double Sustain = rInterpolator.GetFloat(2, sample);
        double Release = rInterpolator.GetFloat(3, sample);
        setEnvelope(Attack, Decay, Sustain, Release);

        int OscMode = (int)rInterpolator.GetFloatOld(5);
        setOsc(static_cast<Oscillator::OscillatorMode>(OscMode));

        int FilterMode = (int)rInterpolator.GetFloatOld(8);
        int FilterLowType = (int)rInterpolator.GetFloatOld(14);
        int FilterBandType = (int)rInterpolator.GetFloatOld(15);
        mFilter.setLowType(static_cast<AugsFilter::LowFilterType>(FilterLowType));
        mFilter.setBandType(static_cast<AugsFilter::BandFilterType>(FilterBandType));

        float FilterCut = rInterpolator.GetFloat(9,sample);
        float FilterRes = rInterpolator.GetFloat(10, sample);
        setFilter(FilterCut, FilterRes, FilterMode);
        
        double Volume = rInterpolator.GetFloat(4, sample);

        double SampleVal = mOsc.nextSample();
        double EnvValue = mEnv.nextSample();
        SampleVal = SampleVal * EnvValue * mVelocity * Volume;
        mFilter.ProcessSample(SampleVal);

        if ((mEnv.getCurrentStage() == EnvelopeGenerator::EnvelopeStage::ENVELOPE_STAGE_OFF) || (EnvValue < minimumValue))
        {
            clearCurrentNote();
            mEnv.enterStage(EnvelopeGenerator::EnvelopeStage::ENVELOPE_STAGE_OFF);
            SampleVal = 0;
        }

        for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
        {
            outputBuffer.addSample(channel, startSample, SampleVal);
        }
        startSample++;
    }
}