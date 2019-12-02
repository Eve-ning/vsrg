#pragma once
#include "BaseObjects/Special/TimingGridMeasure.h"

class TimingGridBase
{
public:
	// If measures always contain the same amount of beats
	TimingGridBase(const size_t measures,
				   const size_t beats,
				   const size_t snaps);	
	~TimingGridBase();

	TimingGridMeasure& operator [](size_t i);

	bool isEmpty() const;

	size_t size() const;
	std::vector<double> getBpmVector() const;
	double length() const;

	// Getting offset is slow when it's large
	// Will see which functions need a much faster access
	double getOffsetAt(const size_t measure_i,
					   const size_t beat_i,
					   const size_t snap_i);

private:
	std::vector<TimingGridMeasure> tgm_v_;
	double offset_ms_;
};

