#include "stdafx.h"
#include "TimingGridBeat.h"

TimingGridBeat::TimingGridBeat(const size_t snaps, const double bpm) :
	tgs_v_(std::vector<TimingGridSnap>(snaps, TimingGridSnap())),
	bpm_(bpm) {}

TimingGridBeat::~TimingGridBeat() {}

TimingGridSnap& TimingGridBeat::operator[](size_t i){
	return tgs_v_[i]; 
}

double TimingGridBeat::getBpm() const { return bpm_; }
void TimingGridBeat::setBpm(double bpm) { bpm_ = bpm; }

bool TimingGridBeat::isEmpty() const {
	for (const auto& tgs : tgs_v_) {
		if (!tgs.isEmpty()) return false;
	}
	return true;
}

bool TimingGridBeat::divide(const size_t by) {
	if (size() % by != 0) return false; // Bad divide
	auto save = tgs_v_; // Branch current state
	
	bool success = true;

	for (size_t counter = 1, i = save.size() - 1;
		 i > 0; // False only when single element
		 i--) {
		if (counter == by) { // Skips if we accumulate to by value
			counter = 0; // Counter adds by 1 again
			continue;
		}
		if (save[i].isEmpty()) save.erase(save.begin() + i);
		else return false;
		counter++;
	}

	tgs_v_ = save; // Save to master
	return true;
}

size_t TimingGridBeat::size() const { return tgs_v_.size(); }

double TimingGridBeat::length(double unit_scale) const { return TimedObject::Units::minute / bpm_; }
double TimingGridBeat::snapLength(double unit_scale) const { return length(unit_scale) / size(); }

