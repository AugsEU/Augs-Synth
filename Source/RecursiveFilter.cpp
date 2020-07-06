/*
  ==============================================================================

    RecursiveFilter.cpp
    Created: 17 Jun 2020 6:59:22pm
    Author:  August

  ==============================================================================
*/

#include "RecursiveFilter.h"

double RecursiveFilter::ProcessSample(double Sample)
{
    size_t NumElements = aCoefs.size();

    PushFrontPopBack(xVal, Sample);
    
    double NewSample = 0.0;

    for (size_t i = 0; i < NumElements;i++)
    {
        NewSample += xVal.at(i) * aCoefs.at(i);
        if (i > 0) NewSample += yVal.at(i) * bCoefs.at(i - 1);
    }
    
    PushFrontPopBack(yVal, NewSample);

    return NewSample;
}

void RecursiveFilter::PushFrontPopBack(std::vector<double>& Vec, double& Value)
{
    size_t NumberElements = Vec.size();
    for (size_t i = 0; i < NumberElements - 1;i++)
    {
        Vec[i + 1] = Vec[i];
    }
    Vec[0] = Value;
}