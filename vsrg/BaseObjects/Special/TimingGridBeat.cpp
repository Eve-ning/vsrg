#include "stdafx.h"
#include "TimingGridBeat.h"

TimingGridBeat::TimingGridBeat(const size_t snaps, const size_t columns) :
	tgs_v_(std::vector<TimingGridSnap>(snaps, TimingGridSnap(columns))) {}

TimingGridBeat::~TimingGridBeat() {}

TimingGridSnap& TimingGridBeat::operator[](size_t i){
	return tgs_v_[i]; 
}

double TimingGridBeat::getBpm() const { return bpm_; }
void TimingGridBeat::setBpm(double bpm) { bpm_ = bpm; }

size_t TimingGridBeat::size() const { return tgs_v_.size(); }

double TimingGridBeat::length(double unit_scale) const { return 1 * unit_scale / (bpm_ * TimedObject::Units::minute); }
double TimingGridBeat::snapLength(double unit_scale) const { return length(unit_scale) / size(); }

