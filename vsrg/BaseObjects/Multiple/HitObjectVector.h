#pragma once
#include "TimedObjectVector.h"
#include "BaseObjects/Singular/Hit/HitObject.h"

#define HO_CAST(obj) std::static_pointer_cast<HitObject>(obj)

class HitObjectVector : public TimedObjectVector
{
public:
	HitObjectVector();
	~HitObjectVector();

	SPtrHitObject operator[](unsigned int index) const {
		return HO_CAST(to_v_[index]);
	}

	std::vector<SPtrHitObject> getHitObjectVector() const {
		std::vector<SPtrHitObject> ho_v;
		for (const auto & ho : to_v_) ho_v.push_back(HO_CAST(ho));
		return ho_v;
	}

	SPtrHitObject getEarliestObject() const {
		return HO_CAST(TimedObjectVector::getEarliestObject());
	}
	SPtrHitObject getLatestObject() const {
		return HO_CAST(TimedObjectVector::getLatestObject());
	}
};

