/*
  ==============================================================================

    RecursiveFilter.h
    Created: 17 Jun 2020 6:59:22pm
    Author:  August

  ==============================================================================
*/
#pragma once
#include <vector>
#include <queue>
#include "Constants.h"

class RecursiveFilter
{
public:
    //Defines a recursive IIR filter
    //bCoef must always be 1 smaller than aCoef
    RecursiveFilter(std::vector<double> aCoef, std::vector<double> bCoef) : aCoefs(aCoef), bCoefs(bCoef), xVal(aCoef.size(),0), yVal(aCoef.size(), 0)
    {

    }
    ~RecursiveFilter() {}
    inline static void SetSampleRate(double Rate) { sampleRate = Rate; };

    double ProcessSample(double Sample);
    virtual void CalculateCoefs(double CutOff, double Res) = 0;
protected:
    static double sampleRate;
    std::vector<double> aCoefs;
    std::deque<double> xVal;
    std::vector<double> bCoefs;
    std::deque<double> yVal;

};
