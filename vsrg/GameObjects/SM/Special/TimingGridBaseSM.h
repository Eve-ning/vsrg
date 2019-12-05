#pragma once
#include "BaseObjects/Special/TimingGridBase.h"

class TimingGridBaseSM :
	public TimingGridBase
{
public:
	// If measures always contain the same amount of beats
	TimingGridBaseSM(size_t measures,
				     size_t beats,
				     size_t snaps,
				     double offset_ms = 0.0,
			         double bpm = 0.0) :
		TimingGridBase(measures,beats, snaps, offset_ms, bpm){}

	~TimingGridBaseSM() {}
};

