/*
  ==============================================================================

    ParameterInterpolator.h
    Created: 25 Jun 2020 6:07:10pm
    Author:  August

  ==============================================================================
*/

#pragma once
#include "Defs.h"
#include "JuceHeader.h"

class ParameterInterpolator
{
public:
    ParameterInterpolator() {}
    ~ParameterInterpolator() {}

    void StartNewBuffer(AudioProcessorValueTreeState& State, int& BuffSize);
    float GetFloat(const int& i, const int& SampleIdx);


private:
    int BufferSize = 0;
    float OldFloatParams[NUM_FLOAT_PARAMS];
    float GoalFloatParams[NUM_FLOAT_PARAMS];

};