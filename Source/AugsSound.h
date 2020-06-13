#pragma once

#include <JuceHeader.h>

class AugsSound : public SynthesiserSound
{
public:

	AugsSound() {}

	bool appliesToNote(int midiNoteNumber) override
	{
		return true;
	}
	bool appliesToChannel(int midiChannel) override
	{
		return true;
	}
};