#include "SineWaveVoice.h"

bool SineWaveVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast<SineWaveSound*> (sound) != nullptr;
}

void SineWaveVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound*, int /*currentPitchWheelPosition*/)
{
    mCurrentAngle = 0.0;
    mLevel = velocity * 0.15;
    mTailOff = 0.0;
    auto cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    auto cyclesPerSample = cyclesPerSecond / getSampleRate();

    mAngleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;
}

void SineWaveVoice::stopNote(float /*velocity*/, bool allowTailOff)
{
    if (allowTailOff)
    {
        if (mTailOff == 0.0)
            mTailOff = 1.0;
    }
    else
    {
        clearCurrentNote();
        mAngleDelta = 0.0;
    }
}

void SineWaveVoice::pitchWheelMoved(int newPitchWheelValue) {}

void SineWaveVoice::controllerMoved(int controllerNumber, int newControllerValue) {}

void SineWaveVoice::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    if (mAngleDelta != 0.0)
    {
        if (mTailOff > 0.0) //decay
        {
            while (--numSamples >= 0)//count down the samples
            {
                auto currentSample = (float)(sin(mCurrentAngle) * mLevel * mTailOff);

                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample(i, startSample, currentSample);

                mCurrentAngle += mAngleDelta;
                ++startSample;

                mTailOff *= 0.99; // decay a bit

                if (mTailOff <= 0.005)//round to 0
                {
                    clearCurrentNote(); // stop playing

                    mAngleDelta = 0.0;
                    break;
                }
            }
        }
        else//sustain
        {
            while (--numSamples >= 0) // [6]
            {
                auto currentSample = (float)(sin(mCurrentAngle) * mLevel);

                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample(i, startSample, currentSample);

                mCurrentAngle += mAngleDelta;
                ++startSample;
            }
        }
    }
}