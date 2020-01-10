#pragma once
#include "BaseObjects/Special/TimingGridBeat.h"

class TimingGridMeasure
{
public:
	// If beats always contain the same amount of snaps
	TimingGridMeasure(size_t beats = 0,
					  size_t snaps = 0,
					  double bpm = 0.0); 
	~TimingGridMeasure();

	TimingGridBeat& operator [](size_t i);
	TimingGridBeat operator [](size_t i) const;

	bool isEmpty() const;

	size_t size() const;
	std::vector<double> getBpm1DVector() const;
	void setBpm1DVector(const std::vector<double>& bpm_v);

	std::vector<TimingGridBeat> getTimingGridBeatVector() const;
	void setTimingGridBeatVector(const std::vector<TimingGridBeat>& tgb_v);

	double length(double unit_scale = TimedObject::Units::msecond) const;

	void simplify(size_t by);

private:
	std::vector<TimingGridBeat> tgb_v_;
};

