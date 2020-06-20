/*
  ==============================================================================

    Filter.cpp
    Created: 15 Jun 2020 9:51:45pm
    Author:  August

  ==============================================================================
*/

#include "AugsFilter.h"

void AugsFilter::ProcessSample(double& Sample)
{
    //if (Sample == 0.0) return;
    double LowPassSample = mFilter.ProcessSample(Sample);

    switch (mMode) 
    {
    case FILTER_LOW_PASS:
        Sample = LowPassSample;
        break;
    case FILTER_HIGH_PASS:
        Sample = Sample - LowPassSample;//subtract low frequences
        break;
    case FILTER_BAND_PASS:
        return;
        break;
    case FILTER_OFF:
        return;
    default:
        return;
    }
}

void AugsFilter::setFreqAndRes(double newFreq, double newRes)
{
    if (mFreq == newFreq && mRes == newRes) return;//don't bother calculating if there are no changes
    mFreq = newFreq; mRes = newRes;//set new values

    mFilter.CalculateCoefs(newFreq, newRes);//update the filter
}