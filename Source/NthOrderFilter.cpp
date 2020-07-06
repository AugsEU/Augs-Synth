/*
  ==============================================================================

    NthOrderFilter.cpp
    Created: 5 Jul 2020 6:34:56pm
    Author:  August

  ==============================================================================
*/

#include "NthOrderFilter.h"
void NthOrderFilter::UpdateParameters(double CutOff, double Res)
{
    mFreq = 2 * CutOff / sampleRate;
    mRes = 1.0 / Res;
    calculateFeedbackAmount();
}

double NthOrderFilter::ProcessSample(double Sample, FilterMode Mode) 
{
    size_t NumBuffers = Buffers.size();
    for (size_t i = 0; i < NumBuffers; i++)
    {
        if (i)// if i is not 0
        {
            Buffers[i] += mFreq * (Buffers[i-1] - Buffers[i]);
        }
        else//if i is 0
        {
            Buffers[0] += mFreq * (Sample - Buffers[0] + mFeedback * (Buffers[0] - Buffers[1]));
        }
    }

    switch (Mode)
    {
    case FILTER_LOW_PASS:
        return Buffers[NumBuffers - 1];//return final buffer
        break;
    case FILTER_HIGH_PASS:
        return Sample - Buffers[NumBuffers - 1];
        break;
    case FILTER_BAND_PASS:
        return Buffers[0] - Buffers[NumBuffers - 1];
        break;
    default:
        return Sample;
        break;
    }
    return Sample;
}