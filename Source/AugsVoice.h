#pragma once

#include <JuceHeader.h>
#include <cmath>
#include "Oscillator.h"
#include "PolyBLEPOscillator.h"
#include "EnvelopeGenerator.h"
#include "AugsSound.h"
#include "Defs.h"
#include "AugsFilter.h"
#include "ParameterInterpolator.h"

class AugsVoice : public SynthesiserVoice
{
public:
	bool canPlaySound(SynthesiserSound* sound) override;
	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
	void stopNote(float velocity, bool allowTailOff) override;
	void pitchWheelMoved(int newPitchWheelValue) override;
	void controllerMoved(int controllerNumber, int newControllerValue) override;
	void renderNextBlock(AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;

	AugsVoice(ParameterInterpolator& Interpolator) :mVelocity(0.0), minimumValue(0.0000001), rInterpolator(Interpolator)
	{}
	~AugsVoice()
	{}
private:
	ParameterInterpolator& rInterpolator;
	const double minimumValue;
	double mVelocity;
	PolyBLEPOscillator mOsc;
	AugsFilter mFilter;
	EnvelopeGenerator mEnv;

	void setEnvelope(double a, double d, double s, double r);
	inline void setOsc(Oscillator::OscillatorMode mode) { mOsc.setMode(mode); }
	inline void setFilter(double Freq, double Res, int Mode)
	{
		mFilter.setFreqAndRes(Freq, Res);
		mFilter.setMode(static_cast<FilterMode>(Mode));
	}


};