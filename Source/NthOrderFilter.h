/*
  ==============================================================================

    NthOrderFilter.h
    Created: 5 Jul 2020 6:34:56pm
    Author:  August

  ==============================================================================
*/

#pragma once
#include <vector>
#include "Defs.h"
#include "Constants.h"
#include "AbstractFilter.h"

class NthOrderFilter : public AbstractFilter
{
public:
    NthOrderFilter(size_t N) : Buffers(N+1), mFreq(0.0), mRes(0.0)
    {}
    ~NthOrderFilter() {}
    double ProcessSample(double Sample, FilterMode Mode);
    void UpdateParameters(double CutOff, double Res);
private:

    inline void calculateFeedbackAmount() { mFeedback = mRes + (mRes / (1.0 - mFreq)); }

    double mFreq;
    double mRes;
    double mFeedback;
    std::vector<double> Buffers;
};