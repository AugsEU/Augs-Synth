#pragma once

#include <JuceHeader.h>
#include <cmath>
#include "Main.h"

class AugsVoice : public SynthesiserVoice
{
public:
	bool canPlaySound(SynthesiserSound* sound) override;
	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
	void stopNote(float velocity, bool allowTailOff) override;
	void pitchWheelMoved(int newPitchWheelValue) override;
	void controllerMoved(int controllerNumber, int newControllerValue) override;
	void renderNextBlock(AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;
	void setEnvelope(double a, double d, double s, double r);
	void setOsc(Oscillator::OscillatorMode mode);
	AugsVoice() :mVelocity(0.0), minimumValue(0.0000001)
	{}
	~AugsVoice()
	{}
private:
	const double minimumValue;
	double mVelocity;
	PolyBLEPOscillator mOsc;
	EnvelopeGenerator mEnv;
};