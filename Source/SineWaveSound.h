#pragma once

#include <JuceHeader.h>

class SineWaveSound : public SynthesiserSound
{
public:

	SineWaveSound() {}

	bool appliesToNote(int midiNoteNumber) override
	{
		return true;
	}
	bool appliesToChannel(int midiChannel) override
	{
		return true;
	}
};