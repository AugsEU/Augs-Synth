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
#include "AbstractFilter.h"

class RecursiveFilter : public AbstractFilter
{
public:
    //Defines a recursive IIR filter
    //bCoef must always be 1 smaller than aCoef
    RecursiveFilter(std::vector<double> aCoef, std::vector<double> bCoef) : AbstractFilter(), aCoefs(aCoef), bCoefs(bCoef), xVal(aCoef.size(),0), yVal(aCoef.size(), 0)
    {

    }
    ~RecursiveFilter() {}
    double ProcessSample(double Sample);
protected:
    std::vector<double> aCoefs;
    std::vector<double> xVal;
    std::vector<double> bCoefs;
    std::vector<double> yVal;
private:
    void PushFrontPopBack(std::vector<double>& Vec, double& Value);
};
