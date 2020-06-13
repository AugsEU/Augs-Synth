#pragma once



typedef struct 
{
    const std::string ID;
    const std::string Name;
    const double minVal;
    const double maxVal;
    const double defaultVal;
    const double skewFactor;
} FloatParam_Properties;

#define NUM_FLOAT_PARAMS 5
const FloatParam_Properties FloatParamProps[NUM_FLOAT_PARAMS] =
{       {"EnvAttack",   "Attack",   0.0,    3.0,    0.1,    0.6},
        {"EnvDecay",    "Decay",    0.0,    3.0,    0.1,    0.7},
        {"EnvSustain",  "Sustain",  0.0,    1.0,    0.5,    0.5},
        {"EnvRelease",  "Release",  0.0,    7.0,    0.1,    0.7},
        {"Volume",      "Volume",   0.0,     0.5,    0.1,   0.2} };