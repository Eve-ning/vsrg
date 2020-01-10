#include "stdafx.h"
#include "TimingGridBaseSM.h"

TimingGridBaseSM::TimingGridBaseSM(size_t measures, size_t beats, size_t snaps, double offset_ms, double bpm) :
	TimingGridBase(measures, beats, snaps, offset_ms, bpm) {}

TimingGridBaseSM::~TimingGridBaseSM() {}

void TimingGridBaseSM::setNotes(const SPtrHitObjectVector& ho_v) {
	for (size_t i = 0; i < ho_v->size(); i++) {
		pushSnap(ho_v->operator[](i)->getOffset(), ho_v->operator[](i));
	}
}
