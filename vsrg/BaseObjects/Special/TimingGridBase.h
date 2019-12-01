#pragma once
#include "BaseObjects/Special/TimingGridMeasure.h"

class TimingGridBase
{
public:
	TimingGridBase(const size_t measures,
				   const size_t beats,
				   const size_t snaps,
				   const size_t columns);	
	~TimingGridBase();

	TimingGridMeasure& operator [](size_t i);

	size_t size() const;

	std::vector<double>& getBpmVector() const;
	double length() const;

private:
	std::vector<TimingGridMeasure> tgm_v_;
};

