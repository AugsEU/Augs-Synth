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
        LowPass(Sample);
        break;
    case FILTER_HIGH_PASS:
        HighPass(Sample);
        break;
    case FILTER_BAND_PASS:
        BandPass(Sample);
        break;
    case FILTER_BAND_REJECT:
        BandReject(Sample);
        break;
    case FILTER_OFF:
        return;
    default:
        return;
    }
}

void AugsFilter::setFreqAndRes(double newFreq, double newRes)
{
    //update the filters
    switch (mLowType)
    {
    case LowFilterType::LOW_SINGLEPOLE:
        mSPFilter.UpdateValues(newFreq, newRes);
        break;
    case LowFilterType::LOW_THIRD_ORDER:
        mThirdOrderFilter.UpdateValues(newFreq, newRes);
        break;
    default:
        break;
    }

    switch (mBandType)
    {
    case BandFilterType::BAND_NARROWBAND:
        mNBFilter.UpdateValues(newFreq, newRes);
        break;
    case BandFilterType::BAND_THIRD_ORDER:
        mThirdOrderFilter.UpdateValues(newFreq, newRes);
        break;
    default:
        break;
    }
}

void AugsFilter::LowPass(double& Sample)
{
    switch (mLowType)
    {
    case LowFilterType::LOW_SINGLEPOLE:
        Sample = mSPFilter.ProcessSample(Sample);
        break;
    case LowFilterType::LOW_THIRD_ORDER:
        Sample = mThirdOrderFilter.ProcessSample(Sample, FILTER_LOW_PASS);
        break;
    default:
        break;
    }
}

void AugsFilter::HighPass(double& Sample)
{
    double OldSampleValue = Sample;
    LowPass(Sample);
    Sample = OldSampleValue - Sample;
}

void AugsFilter::BandPass(double& Sample)
{
    switch (mBandType)
    {
    case BandFilterType::BAND_NARROWBAND:
        Sample = mNBFilter.ProcessSample(Sample);
        break;
    case BandFilterType::BAND_THIRD_ORDER:
        Sample = mThirdOrderFilter.ProcessSample(Sample, FILTER_BAND_PASS);
        break;
    default:
        break;
    }
}

void AugsFilter::BandReject(double& Sample)
{
    double OldSampleValue = Sample;
    BandPass(Sample);
    Sample = OldSampleValue - Sample;
}