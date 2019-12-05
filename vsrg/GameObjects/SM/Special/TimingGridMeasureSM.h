#pragma once
#include "BaseObjects/Special/TimingGridMeasure.h"

class TimingGridMeasureSM :
	public TimingGridMeasure
{
public:
	// If beats always contain the same amount of snaps
	TimingGridMeasureSM(size_t beats,
						size_t snaps,
						double bpm = 0.0) :
		TimingGridMeasure(beats, snaps, bpm) {}
	~TimingGridMeasureSM() {}
};

