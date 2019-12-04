#pragma once
#include "BaseObjects/Special/TimingGridMeasure.h"

class TimingGridBase
{
public:
	// If measures always contain the same amount of beats
	TimingGridBase(const size_t measures,
				   const size_t beats,
				   const size_t snaps,
				   const double offset_ms = 0.0,
			       const double bpm = 0.0);	
	~TimingGridBase();

	TimingGridMeasure& operator [](size_t i);

	bool isEmpty() const;

	size_t size() const;
	std::vector<double> getBpmVector() const;
	double length() const;

	std::vector<double> getBpm1DVector() const;
	void setBpm1DVector(const std::vector<double>& bpm_v);
	std::vector<std::vector<double>> getBpm2DVector() const;
	void setBpm2DVector(const std::vector<std::vector<double>>& bpm_2v);

	// Getting offset is slow when it's large
	// Will see which functions need a much faster access
	double getOffsetAt(const size_t measure_i,
					   const size_t beat_i,
					   const size_t snap_i);

private:
	std::vector<TimingGridMeasure> tgm_v_;
	double offset_ms_;
};

