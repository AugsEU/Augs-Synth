/*
  ==============================================================================

    NarrowBand.cpp
    Created: 26 Jun 2020 6:56:00pm
    Author:  August

  ==============================================================================
*/

#include "NarrowBand.h"

void NarrowBand::UpdateParameters(double CutOff, double Res)//Here the res actually controls the band width. This is a band reject filter
{
    double Freq = CutOff / sampleRate;
    if (Freq > 0.5) Freq = 0.5;     if (Freq < 0.0) Freq = 0.0;
    double BW = 1.0 / (2.0 * Res);
    if (BW < 0.0) BW = 0.0; if (BW > 0.5) BW = 0.5;

    double CPF = 2.0 * cos(TWO_PI * Freq);
    double R = 1.0 - (3.0 * BW);
    double R2 = R * R;
    double K = (1.0 - (R * CPF) + R2) / (2.0 - CPF);

    aCoefs[0] = 1.0-K;
    aCoefs[1] = (K-R) * CPF;
    aCoefs[2] = R2-K;
    bCoefs[0] = R * CPF;
    bCoefs[1] = -R2;
}