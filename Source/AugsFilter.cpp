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
    switch (mMode) 
    {
    case FILTER_LOW_PASS:
        Sample = mFilter.lores(Sample, mFreq, mRes);
        break;
    case FILTER_HIGH_PASS:
        Sample = mFilter.hires(Sample, mFreq, mRes);
        break;
    case FILTER_BAND_PASS:
        Sample = mFilter.bandpass(Sample, mFreq, mRes);
        break;
    case FILTER_OFF:
        return;
    default:
        return;
    }
}