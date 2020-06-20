/*
  ==============================================================================

    SinglePoleFilter.cpp
    Created: 20 Jun 2020 6:04:43pm
    Author:  August

  ==============================================================================
*/

#include "SinglePoleFilter.h"


void SinglePoleFilter::CalculateCoefs(double CutOff, double Res)
{
    double Freq = CutOff / sampleRate;
    double x = exp(-TWO_PI * Freq);
    aCoefs[0] = 1.0 - x;
    bCoefs[0] = x;
}