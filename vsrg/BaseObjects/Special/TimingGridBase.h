#pragma once
#include "BaseObjects/Special/TimingGridMeasure.h"
#include "BaseObjects/Multiple/EventObjectVector.h"
#include "BaseObjects/Multiple/HitObjectVector.h"
#include "BaseObjects/Singular/Event/TimingPoint.h"

class TimingGridBase
{
public:
	// If measures always contain the same amount of beats
	TimingGridBase(size_t measures = 0,
				   size_t beats = 0,
				   size_t snaps = 0,
				   double offset_ms = 0.0,
			       double bpm = 0.0);

	~TimingGridBase();

	TimingGridMeasure& operator [](size_t i);
	TimingGridMeasure operator [](size_t i) const;

	bool isEmpty() const;

	size_t size() const;
	double length() const;

	std::vector<double> getBpm1DVector() const;
	void setBpm1DVector(const std::vector<double>& bpm_v);
	std::vector<std::vector<double>> getBpm2DVector() const;
	void setBpm2DVector(const std::vector<std::vector<double>>& bpm_2v);

	std::vector<TimingGridMeasure> getTimingGridMeasureVector() const;
	void setTimingGridMeasureVector(const std::vector<TimingGridMeasure>& tgm_v);

	void setOffset(double offset_ms, double unit_scale = TimedObject::Units::msecond);

	double getOffset() const;
	double getOffset(const TimingGridIndex& index) const;// Getting offset is slow when it's large
	double getOffset(size_t measure,
					 size_t beat,
				     size_t snap) const;

	// Uses an offset to estimate the index
	TimingGridIndex getIndex(double offset_ms,
							 double unit_scale = TimedObject::Units::msecond,
							 bool extend = false);

	// Grabs a snap by reference from index
	TimingGridSnap& getSnap(const TimingGridIndex& index) const;
	TimingGridSnap& getSnap(const TimingGridIndex& index);
	TimingGridSnap& getSnap(double offset_ms,
						    double unit_scale = TimedObject::Units::msecond) const;
	TimingGridSnap& getSnap(double offset_ms,
						    double unit_scale = TimedObject::Units::msecond);

	void setSnap(const TimingGridIndex& index,
				 const std::vector<SPtrHitObject>& ho_v);
	void setSnap(double offset_ms,
				 const std::vector<SPtrHitObject>& ho_v,
				 double unit_scale = TimedObject::Units::msecond);
	void pushSnap(const TimingGridIndex& index,
				  const SPtrHitObject& ho);
	void pushSnap(double offset_ms,
				  const SPtrHitObject& ho,
				  double unit_scale = TimedObject::Units::msecond);
	void pushMeasure(const TimingGridMeasure& tgm);

private:

	std::vector<TimingGridMeasure> tgm_v_;
	double offset_ms_;
};

