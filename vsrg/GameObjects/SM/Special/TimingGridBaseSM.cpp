#include "stdafx.h"
#include "TimingGridBaseSM.h"

TimingGridBaseSM::TimingGridBaseSM(size_t measures, size_t beats, size_t snaps, double offset_ms, double bpm) :
	TimingGridBase(measures, beats, snaps, offset_ms, bpm) {}

TimingGridBaseSM::~TimingGridBaseSM() {}
