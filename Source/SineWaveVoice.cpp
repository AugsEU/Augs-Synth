#include "SineWaveVoice.h"

bool SineWaveVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast<SineWaveSound*> (sound) != nullptr;
}

void SineWaveVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound*, int /*currentPitchWheelPosition*/)
{
    mLevel = velocity * 0.05;
    mFreq = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    mEnv.trigger = 1;
}

void SineWaveVoice::setEnvelope(double a, double d, double s, double r)
{
    mEnv.setAttack(a);
    mEnv.setDecay(d);
    mEnv.setSustain(s);
    mEnv.setRelease(r);
}

void SineWaveVoice::stopNote(float /*velocity*/, bool allowTailOff)
{
    clearCurrentNote();
    mEnv.trigger = 0;
}

void SineWaveVoice::pitchWheelMoved(int newPitchWheelValue) {}

void SineWaveVoice::controllerMoved(int controllerNumber, int newControllerValue) {}

void SineWaveVoice::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    for (int sample = 0; sample < numSamples; sample++)
    {
        double SampleVal = mOsc.saw(mFreq);
        SampleVal = mEnv.adsr(SampleVal, mEnv.trigger);
        for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
        {
            outputBuffer.addSample(channel, startSample, SampleVal);
        }
        startSample++;
    }
}