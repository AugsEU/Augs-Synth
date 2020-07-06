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
    ParameterInterpolator() 
    {
        for (int i = 0; i < NUM_FLOAT_PARAMS; i++)
        {
            OldFloatParams[i] = 0;
            GoalFloatParams[i] = 0;
        }
    }
    ~ParameterInterpolator() {}

    void StartNewBuffer(AudioProcessorValueTreeState& State, int& BuffSize);
    float GetFloat(const int& i, const int& SampleIdx);
    float GetFloatOld(const int& i);

private:
    int BufferSize = 0;
    float OldFloatParams[NUM_FLOAT_PARAMS];
    float GoalFloatParams[NUM_FLOAT_PARAMS];

};