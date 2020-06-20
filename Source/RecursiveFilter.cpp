/*
  ==============================================================================

    RecursiveFilter.cpp
    Created: 17 Jun 2020 6:59:22pm
    Author:  August

  ==============================================================================
*/

#include "RecursiveFilter.h"

double RecursiveFilter::sampleRate = 44100.0;

double RecursiveFilter::ProcessSample(double Sample)
{
    xVal.push_front(Sample);//Add new sample
    xVal.pop_back();//Pop oldest
    double NewSample = 0.0;
    size_t NumElements = aCoefs.size();
    for (size_t i = 0; i < NumElements;i++)
    {
        NewSample += xVal.at(i) * aCoefs.at(i);
        if (i > 0) NewSample += yVal.at(i) * bCoefs.at(i - 1);
    }
    yVal.push_front(NewSample);
    yVal.pop_back();
    return NewSample;
}