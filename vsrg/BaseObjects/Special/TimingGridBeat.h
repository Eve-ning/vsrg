#pragma once
#include "BaseObjects/Special/TimingGridSnap.h"


class TimingGridBeat
{
public:
	TimingGridBeat(const size_t snaps,
				   const size_t columns);
	~TimingGridBeat();

	TimingGridSnap& operator [](size_t i);
	double getBpm() const;
	void setBpm(double bpm);

	size_t size() const;

	double length(double unit_scale = TimedObject::Units::msecond) const;
	double snapLength(double unit_scale = TimedObject::Units::msecond) const;

private:
	std::vector<TimingGridSnap> tgs_v_;
	double bpm_;
	// We'll consider the lowest possible point where a BPM seems feasible
};

