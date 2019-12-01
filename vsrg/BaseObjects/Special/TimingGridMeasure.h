#pragma once
#include "BaseObjects/Special/TimingGridBeat.h"

class TimingGridMeasure
{
public:
	TimingGridMeasure(const size_t beats,
					  const size_t snaps,
				      const size_t columns);
	~TimingGridMeasure();

	TimingGridBeat& operator [](size_t i);

	size_t size() const;
	std::vector<double>& getBpmVector() const;

	double length(double unit_scale = TimedObject::Units::msecond) const;

private:
	std::vector<TimingGridBeat> tgb_v_;
};

