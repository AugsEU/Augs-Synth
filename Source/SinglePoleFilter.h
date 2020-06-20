/*
  ==============================================================================

    SinglePoleFilter.h
    Created: 20 Jun 2020 6:04:43pm
    Author:  August

  ==============================================================================
*/

#pragma once
#include "RecursiveFilter.h"
#include <math.h>

class SinglePoleFilter : public RecursiveFilter
{
public:
    SinglePoleFilter() : RecursiveFilter({ 0.5,0.0 }, { 0.5 })
    {

    }
    void CalculateCoefs(double CutOff, double Res);
};