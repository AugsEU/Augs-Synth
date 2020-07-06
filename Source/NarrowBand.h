/*
  ==============================================================================

    NarrowBand.h
    Created: 26 Jun 2020 6:56:00pm
    Author:  August

  ==============================================================================
*/

#pragma once
#include "RecursiveFilter.h"
#include <math.h>

class NarrowBand : public RecursiveFilter
{
public:
    NarrowBand() : RecursiveFilter({ 0.0, 0.0, 0.0 }, {0.0, 0.0})
    {
        double F = sampleRate / 4.0;
        UpdateParameters(F, 2.0);
    }
    void UpdateParameters(double CutOff, double Res);
};