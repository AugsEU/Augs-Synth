/*
  ==============================================================================

    SinglePoleFilter.cpp
    Created: 20 Jun 2020 6:04:43pm
    Author:  August

  ==============================================================================
*/

#include "SinglePoleFilter.h"


void SinglePoleFilter::UpdateParameters(double CutOff, double Res)
{
    if (CutOff < 0) CutOff = 0;
    double Freq = CutOff / sampleRate;
    if (Freq > 0.5) CutOff = 0.5;
    double x = exp(-TWO_PI * Freq);
    aCoefs[0] = 1.0 - x;
    bCoefs[0] = x;
}