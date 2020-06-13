#pragma once

#include <cmath>

class EnvelopeGenerator {
public:
	enum EnvelopeStage {
		ENVELOPE_STAGE_OFF = 0,
		ENVELOPE_STAGE_ATTACK,
		ENVELOPE_STAGE_DECAY,
		ENVELOPE_STAGE_SUSTAIN,
		ENVELOPE_STAGE_RELEASE,
		kNumEnvelopeStages
	};


	const double minimumLevel;

	double nextSample();
	void enterStage(EnvelopeStage newStage);
	static void setSampleRate(double newSampleRate);
	void setStageValue(EnvelopeStage stage, double value);


	void reset() {
		currentStage = ENVELOPE_STAGE_OFF;
		currentLevel = minimumLevel;
		multiplier = 1.0;
		currentSampleIndex = 0;
		nextStageSampleIndex = 0;
	}

	inline EnvelopeStage getCurrentStage() const { return currentStage; };

	EnvelopeGenerator() :
		minimumLevel(0.0001),
		currentStage(ENVELOPE_STAGE_OFF),
		currentLevel(minimumLevel),
		multiplier(1.0),
		currentSampleIndex(0),
		nextStageSampleIndex(0) {
		stageValue[ENVELOPE_STAGE_OFF] = 0.0;
		stageValue[ENVELOPE_STAGE_ATTACK] = 0.01;
		stageValue[ENVELOPE_STAGE_DECAY] = 0.5;
		stageValue[ENVELOPE_STAGE_SUSTAIN] = 0.1;
		stageValue[ENVELOPE_STAGE_RELEASE] = 1.0;
	};

private:
	static double sampleRate;
	EnvelopeStage currentStage;
	double currentLevel;
	double multiplier;
	double stageValue[kNumEnvelopeStages];

	void calculateMultiplier(double startLevel, double endLevel, unsigned long long lengthInSamples);
	unsigned long long currentSampleIndex;
	unsigned long long nextStageSampleIndex;
};