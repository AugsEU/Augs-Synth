#pragma once
#include <math.h>

class Oscillator 
{
public:
	enum OscillatorMode 
	{
		OSCILLATOR_MODE_SINE = 0,
		OSCILLATOR_MODE_SAW,
		OSCILLATOR_MODE_SQUARE,
		OSCILLATOR_MODE_TRIANGLE,
		kNumOscillatorModes
	};
	void setMode(OscillatorMode mode);
	void setFrequency(double frequency);
	void setSampleRate(double sampleRate);
	void generate(double* buffer, int nFrames);
	void setPitchMod(double amount);
	double nextSample();
	Oscillator() :
		mOscillatorMode(OSCILLATOR_MODE_SINE),
		mPI(2 * acos(0.0)),
		twoPI(2 * mPI),
		mFrequency(440.0),
		mPitchMod(0.0),
		mPhase(0.0)
	{
		updateIncrement();
	};
	void reset() { mPhase = 0.0; }
protected:
	OscillatorMode mOscillatorMode;
	const double mPI;
	const double twoPI;
	double mFrequency;
	double mPhase;
	static double mSampleRate;;
	double mPhaseIncrement;
	void updateIncrement();
	double mPitchMod;
	double naiveWaveformForMode(OscillatorMode mode);
};

