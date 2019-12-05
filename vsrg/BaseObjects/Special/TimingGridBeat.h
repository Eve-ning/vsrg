#pragma once
#include "BaseObjects/Special/TimingGridSnap.h"

class TimingGridBeat
{
public:
	TimingGridBeat(size_t snaps, double bpm = 0.0);
	~TimingGridBeat();

	TimingGridSnap& operator [](size_t i);
	TimingGridSnap operator [](size_t i) const;
	double getBpm() const;
	void setBpm(double bpm);

	std::vector<TimingGridSnap> getTimingGridSnapVector() const;
	void setTimingGridSnapVector(const std::vector<TimingGridSnap>& tgs_v);

	bool isEmpty() const;
	bool divide(const size_t by);

	size_t size() const;

	double length(double unit_scale = TimedObject::Units::msecond) const;
	double snapLength(double unit_scale = TimedObject::Units::msecond) const;

private:
	std::vector<TimingGridSnap> tgs_v_;
	double bpm_;
	// We'll consider the lowest possible point where a BPM seems feasible
};

/* Footnote
	This system doesn't support fractional beat cut:

	That is, a beat cannot happen during a beat, if needed, the previous beat MUST
	be intentionally sped up

	Personally think it's not worth implementing since it's uncommon to have a 
	reset during a beat
*/

