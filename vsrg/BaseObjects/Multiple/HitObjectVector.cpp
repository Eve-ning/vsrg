#include "stdafx.h"
#include "HitObjectVector.h"

#define HO_CAST(obj) std::static_pointer_cast<HitObject>(obj)

HitObjectVector::HitObjectVector() : TimedObjectVector() {}
HitObjectVector::~HitObjectVector() {}

SPtrHitObject HitObjectVector::operator[](unsigned int index) const {
	return HO_CAST(to_v_[index]);
}

std::vector<SPtrHitObject> HitObjectVector::getHitObjectVector() const {
	std::vector<SPtrHitObject> ho_v;
	for (const auto & ho : to_v_) ho_v.push_back(HO_CAST(ho));
	return ho_v;
}


SPtrHitObject HitObjectVector::getEarliestObject() const {
	return HO_CAST(TimedObjectVector::getEarliestObject());
}
SPtrHitObject HitObjectVector::getLatestObject() const {
	return HO_CAST(TimedObjectVector::getLatestObject());
}
