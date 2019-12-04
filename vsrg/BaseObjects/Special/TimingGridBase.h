#pragma once
#include "BaseObjects/Special/TimingGridMeasure.h"
#include "BaseObjects/Multiple/EventObjectVector.h"
#include "BaseObjects/Multiple/HitObjectVector.h"
#include "BaseObjects/Singular/Event/TimingPoint.h"

// Temp include for intellisense
#include "GameObjects/SM/Singular/Event/TimingPointSM.h"

class TimingGridBase
{
public:
	// If measures always contain the same amount of beats
	TimingGridBase(size_t measures,
				   size_t beats,
				   size_t snaps,
				   double offset_ms = 0.0,
			       double bpm = 0.0);

	template<class TimingPointClass>
	TimingGridBase(const SPtrEventObjectVector& eo_v,
				   const SPtrHitObjectVector& ho_v) {
		auto tp_v = eo_v->getClassOnly<TimingPointClass>();
		
		// Sorts the vector
		std::sort(tp_v.begin(), tp_v.end()); 
			//[](const TimingPointClass& i, const TimingPointClass& j) {
			//	return i.getOffset() < j.getOffset();
			//});
		
	}
	~TimingGridBase();

	TimingGridMeasure& operator [](size_t i);

	bool isEmpty() const;

	size_t size() const;
	double length() const;

	std::vector<double> getBpm1DVector() const;
	void setBpm1DVector(const std::vector<double>& bpm_v);
	std::vector<std::vector<double>> getBpm2DVector() const;
	void setBpm2DVector(const std::vector<std::vector<double>>& bpm_2v);

	std::vector<TimingGridMeasure> getTimingGridMeasureVector() const;
	void setTimingGridMeasureVector(const std::vector<TimingGridMeasure>& tgm_v);

	// Getting offset is slow when it's large
	// Will see which functions need a much faster access
	double getOffset(const TimingGridIndex& index);
	double getOffset(size_t measure,
					 size_t beat,
				     size_t snap);

	TimingGridIndex getIndex(const double& offset);
	TimingGridSnap& getSnap(const TimingGridIndex& index);
	void setSnap(const TimingGridIndex& index,
				 const std::vector<SPtrHitObject>& ho_v);
	void pushSnap(const TimingGridIndex& index,
				  const SPtrHitObject& ho);


private:

	std::vector<TimingGridMeasure> tgm_v_;
	double offset_ms_;
};

