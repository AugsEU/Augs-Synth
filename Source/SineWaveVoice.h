#pragma once

#include <JuceHeader.h>
#include <SineWaveSound.h>
#include <cmath>

class SineWaveVoice : public SynthesiserVoice
{
public:
	bool canPlaySound(SynthesiserSound* sound) override;
	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
	void stopNote(float velocity, bool allowTailOff) override;
	void pitchWheelMoved(int newPitchWheelValue) override;
	void controllerMoved(int controllerNumber, int newControllerValue) override;
	void renderNextBlock(AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;
private:
	double mCurrentAngle = 0.0, mAngleDelta = 0.0, mLevel = 0.0, mTailOff = 0.0;
};