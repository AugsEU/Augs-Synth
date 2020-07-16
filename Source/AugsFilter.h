/*
  ==============================================================================

    Filter.h
    Created: 15 Jun 2020 9:51:57pm
    Author:  August

  ==============================================================================
*/

#pragma once
#include "SinglePoleFilter.h"
#include "NarrowBand.h"
#include "NthOrderFilter.h"

class AugsFilter
{
public:
	enum LowFilterType
	{
		LOW_SINGLEPOLE = 0,
		LOW_THIRD_ORDER,
		kNumLowFilterTypes
	};

	enum BandFilterType
	{
		BAND_NARROWBAND = 0,
		BAND_THIRD_ORDER,
		kNumBandFilterTypes
	};

	void setFreqAndRes(double newFreq, double newRes);
	void setMode(FilterMode newMode) { mMode = newMode; }
	void setLowType(LowFilterType newType) { mLowType = newType; }
	void setBandType(BandFilterType newType) { mBandType = newType; }
	void ProcessSample(double& Sample);

	AugsFilter() : 
		mMode(FILTER_OFF),
		mLowType(LowFilterType::LOW_THIRD_ORDER),
		mBandType(BandFilterType::BAND_THIRD_ORDER),
		mThirdOrderFilter(3)
	{}
	~AugsFilter() {}
private:
	void LowPass(double& Sample);
	void HighPass(double& Sample);
	void BandPass(double& Sample);
	void BandReject(double& Sample);

	FilterMode mMode;
	LowFilterType mLowType;
	BandFilterType mBandType;

	//Multi-type filters
	NthOrderFilter mThirdOrderFilter;

	//Low pass filters
	SinglePoleFilter mSPFilter;

	//Band pass filters
	NarrowBand mNBFilter;
};