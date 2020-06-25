/*
  ==============================================================================

    ParameterInterpolator.cpp
    Created: 25 Jun 2020 6:07:10pm
    Author:  August

  ==============================================================================
*/

#include "ParameterInterpolator.h"

void ParameterInterpolator::StartNewBuffer(AudioProcessorValueTreeState& State, int& BuffSize)
{
    for (int i = 0; i < NUM_FLOAT_PARAMS; i++)
    {
        OldFloatParams[i] = GoalFloatParams[i];
    }
    
    for (int i = 0; i < NUM_FLOAT_PARAMS; i++)
    {
        GoalFloatParams[i] = State.getParameterAsValue(FloatParamProps[i].ID).getValue();
    }

    BufferSize = BuffSize;
}

float ParameterInterpolator::GetFloat(const int& i, const int& SampleIdx)
{
    float Multiplyer = (float)SampleIdx / (float)BufferSize;
    return OldFloatParams[i] + Multiplyer*(GoalFloatParams[i] - OldFloatParams[i]);
}