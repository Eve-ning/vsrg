#pragma once
#include <vector>
#include "BaseObjects/Singular/Hit/HitObject.h"

// To faciliate index API
struct TimingGridIndex {
	TimingGridIndex(size_t snap_ = 0,
					size_t beat_ = 0,
					size_t measure_ = 0) :
		snap(snap_), beat(beat_), measure(measure_) {}
	size_t snap = 0, beat = 0, measure = 0;
};

class TimingGridSnap
{
public:
	TimingGridSnap();
	~TimingGridSnap();

	SPtrHitObject& operator [](size_t i);
	std::vector<SPtrHitObject> getHitObjectVector() const;
	void setHitObjectVector(const std::vector<SPtrHitObject>& ho_v);

	void push_back(SPtrHitObject ho);

	bool isEmpty() const;

	size_t size() const;

private:
	std::vector<SPtrHitObject> ho_v_;
};

