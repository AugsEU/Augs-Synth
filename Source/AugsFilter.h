/*
  ==============================================================================

    Filter.h
    Created: 15 Jun 2020 9:51:57pm
    Author:  August

  ==============================================================================
*/

#pragma once
#include "SinglePoleFilter.h"


class AugsFilter
{
public:
	enum FilterMode
	{
		FILTER_LOW_PASS = 0,
		FILTER_HIGH_PASS,
		FILTER_BAND_PASS,
		FILTER_OFF,
		kNumOscillatorModes
	};
	void setFreqAndRes(double newFreq, double newRes);
	void setMode(FilterMode newMode) { mMode = newMode; }
	void ProcessSample(double& Sample);

	AugsFilter() : mMode(FILTER_OFF), mFreq(0.0), mRes(1.0) {}
	~AugsFilter() {}
private:
	FilterMode mMode;
	double mFreq;
	double mRes;
	SinglePoleFilter mFilter;
};