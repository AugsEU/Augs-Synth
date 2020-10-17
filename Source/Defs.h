#pragma once
#include <string>

#define NUM_VOICES 8
#define FREQ_A 440.0f

typedef struct 
{
    const std::string ID;
    const std::string Name;
    const double minVal;
    const double maxVal;
    const double defaultVal;
    const double skewFactor;
} FloatParam_Properties;

#define NUM_FLOAT_PARAMS 17
const FloatParam_Properties FloatParamProps[NUM_FLOAT_PARAMS] =
{       {"EnvAttack",   "Attack",   0.0,    3.0,    0.1,    0.6},//0
        {"EnvDecay",    "Decay",    0.0,    3.0,    0.1,    0.7},//1
        {"EnvSustain",  "Sustain",  0.0,    1.0,    0.5,    0.5},//2
        {"EnvRelease",  "Release",  0.0,    7.0,    0.1,    0.7},//3
        {"Volume",      "Volume",   0.0,    0.5,    0.1,    0.4},//4
        {"Osc_select",  "Wave form",0.0,    3.0,    0.0,    1.0},//5
        {"PowDist",     "Pow dist", 0.4,    5.0,    1.0,    0.7},
        {"TrimDist",    "Trim dist",0.0,    0.99,   0.0,    2.3},
        {"FilterTyp", "Filter type",0.0,    4.0,    0.0,    1.0},//8
        {"CutOff",      "Cut Off",  50.0,   20000.0,1000.0, 0.3},
        {"FiltRes",    "Resonance", 1.0,    10.0,   3.0,    0.6},
        {"DelayVol",    "DlyVol",   0.0,    1.0,    0.0,    0.7},//11
        {"DelayFall",   "DlyFll",   0.0,    1.0,    0.5,    0.7}, //12
        {"DelayTime",   "DlyTm",    0.0,    2.0,    0.5,    0.6}, //13
        {"LowTyp",      "Low type", 0.0,    1.0,    0.0,    1.0}, //14
        {"BandTyp",     "Band type",0.0,    1.0,    0.0,    1.0}, //15
        {"Tuning",  "Scale Tuning" ,0.0,    2.0,    0.0,    1.0} }; //16

//Filter Enums
enum FilterMode
{
    FILTER_OFF = 0,
    FILTER_LOW_PASS,
    FILTER_HIGH_PASS,
    FILTER_BAND_PASS,
    FILTER_BAND_REJECT,
    kNumFilterModes
};
