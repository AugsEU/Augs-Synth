#include "AugsVoice.h"

bool AugsVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast<AugsSound*> (sound) != nullptr;
}

void AugsVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound*, int /*currentPitchWheelPosition*/)
{
    mVelocity = velocity;
    mOsc.setFrequency(MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    mEnv.enterStage(EnvelopeGenerator::EnvelopeStage::ENVELOPE_STAGE_ATTACK);
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
        float FilterCut = rInterpolator.GetFloat(9,sample);
        float FilterRes = rInterpolator.GetFloat(10, sample);
        setFilter(FilterCut, FilterRes, FilterMode);

        double SampleVal = mOsc.nextSample();
        double EnvValue = mEnv.nextSample();
        SampleVal = SampleVal * EnvValue * mVelocity;
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