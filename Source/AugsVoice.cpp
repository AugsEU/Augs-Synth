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

void AugsVoice::setOsc(Oscillator::OscillatorMode mode)
{
    mOsc.setMode(mode);
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
        double SampleVal = mOsc.nextSample();
        double EnvValue = mEnv.nextSample();
        SampleVal = SampleVal * EnvValue * mVelocity;
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