/*
  ==============================================================================

    DelayEffect.h
    Created: 9 Jul 2020 5:28:11pm
    Author:  August

  ==============================================================================
*/

#pragma once
#include <vector>
#include <memory>

class DelayEffect
{
public:
    DelayEffect() :
        mVolume(0.0f), mFallOff(0.5f), mDelayTime(64), mWriteIdx(0),mSampleBuffer(new std::vector<float>(128))//Default Values
    {
        mReadIdx = (mWriteIdx - mDelayTime) % mSampleBuffer->size();
    }

    ~DelayEffect() 
    {

    }
    void ResizeBuffer(size_t NewSize);
    void UpdateParameters(float Volume, float FallOff, float TimeInSeconds, size_t SampleTime);
    float ProcessSample(float Sample);
private:
    float mVolume;
    float mFallOff;
    float mCalculatedFallOff;
    size_t mDelayTime;//Time of delay, given in samples

    std::unique_ptr<std::vector<float>> mSampleBuffer;
    size_t mWriteIdx;
    size_t mReadIdx;
};