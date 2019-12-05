#pragma once
#include "BaseObjects/Special/TimingGridBeat.h"

class TimingGridBeatSM :
	public TimingGridBeat
{
public:
	TimingGridBeatSM(size_t snaps, double bpm = 0.0) :
		TimingGridBeat(snaps, bpm) {};
	~TimingGridBeatSM() {}
}

