#pragma once
#include "BaseObjects/Special/TimingGridBeat.h"

class TimingGridMeasure
{
public:
	// If beats always contain the same amount of snaps
	TimingGridMeasure(const size_t beats,
					  const size_t snaps); 
	~TimingGridMeasure();

	TimingGridBeat& operator [](size_t i);

	bool isEmpty() const;

	size_t size() const;
	std::vector<double> getBpmVector() const;
	double length(double unit_scale = TimedObject::Units::msecond) const;

	void simplify(size_t by);

private:
	std::vector<TimingGridBeat> tgb_v_;
};

