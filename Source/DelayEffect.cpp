/*
  ==============================================================================

    DelayEffect.cpp
    Created: 9 Jul 2020 5:28:11pm
    Author:  August

  ==============================================================================
*/

#include "DelayEffect.h"

void DelayEffect::ResizeBuffer(const size_t NewSize)
{
    if (mSampleBuffer->size() == NewSize) return; //dont bother with

    mSampleBuffer->resize(NewSize, 0.0f);
    if (mDelayTime > (NewSize - 1)) mDelayTime = NewSize - 1;
    mWriteIdx = mWriteIdx % NewSize;
    mReadIdx = (mWriteIdx - mDelayTime) % NewSize;
}

void DelayEffect::UpdateParameters(float Volume, float FallOff, size_t SampleTime)
{
    //set these two is cheap
    mVolume = Volume;
    mFallOff = FallOff;

    if (mDelayTime == SampleTime) return;
    mDelayTime = SampleTime;//set the delay time

    size_t BuffSize = mSampleBuffer->size();
    if(mDelayTime > (BuffSize - 1)) mDelayTime = BuffSize - 1;//delay time can't be bigger than the buffer - 1 

    mReadIdx = (mWriteIdx - mDelayTime) % BuffSize;//Read
}

float DelayEffect::ProcessSample(float Sample)
{
    size_t BuffSize = mSampleBuffer->size();
    float BackSample = (*mSampleBuffer)[mReadIdx];//sample at the back of the buffer
    mReadIdx = (mReadIdx + 1) % BuffSize;
    mWriteIdx = (mWriteIdx + 1) % BuffSize;

    float NewSample = BackSample * mFallOff + Sample;
    if (NewSample > 1.0f) NewSample = 1.0f;
    if (NewSample < -1.0f) NewSample = -1.0f;

    (*mSampleBuffer)[mWriteIdx] = NewSample;//write sample to buffer and also add a 0
    return BackSample * mVolume;
}