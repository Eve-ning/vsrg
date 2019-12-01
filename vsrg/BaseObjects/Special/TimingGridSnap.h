#pragma once
#include <vector>
#include "BaseObjects/Singular/Hit/HitObject.h"
class TimingGridSnap
{
public:
	TimingGridSnap(const size_t columns);
	~TimingGridSnap();

	SPtrHitObject operator [](size_t i);
	std::vector<SPtrHitObject>& getHitObjectVector();
	void setHitObjectVector(const std::vector<SPtrHitObject>& ho_v);

	size_t size() const;

private:
	std::vector<SPtrHitObject> ho_v_;
};

