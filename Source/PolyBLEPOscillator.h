#pragma once
#include "Oscillator.h"

class PolyBLEPOscillator : public Oscillator 
{
public:
	PolyBLEPOscillator() : lastOutput(0.0) { Oscillator::updateIncrement(); };
	double nextSample();
private:
	double poly_blep(double t);
	double lastOutput;
};