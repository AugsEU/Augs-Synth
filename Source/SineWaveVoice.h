#pragma once

#include <JuceHeader.h>
#include <SineWaveSound.h>
#include <cmath>
#include "maximilian.h"

class SineWaveVoice : public SynthesiserVoice
{
public:
	bool canPlaySound(SynthesiserSound* sound) override;
	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
	void stopNote(float velocity, bool allowTailOff) override;
	void pitchWheelMoved(int newPitchWheelValue) override;
	void controllerMoved(int controllerNumber, int newControllerValue) override;
	void renderNextBlock(AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;
	void setEnvelope(double a, double d, double s, double r);
private:
	double mFreq = 0.0;
	double mLevel = 0.0;
	maxiOsc mOsc;
	maxiEnv mEnv;
};