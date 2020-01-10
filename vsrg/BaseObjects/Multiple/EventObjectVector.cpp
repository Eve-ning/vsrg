#include "stdafx.h" 
#include "EventObjectVector.h"

#define EO_CAST(obj) std::static_pointer_cast<EventObject>(obj)

EventObjectVector::EventObjectVector() : TimedObjectVector() {}
EventObjectVector::~EventObjectVector() {}

SPtrEventObject EventObjectVector::operator[](unsigned int index) const {
	return EO_CAST(to_v_[index]);
}

std::vector<SPtrEventObject> EventObjectVector::getEventObjectVector() const {
	std::vector<SPtrEventObject> eo_v;
	for (const auto & eo : to_v_) eo_v.push_back(EO_CAST(eo));
	return eo_v;
}

SPtrEventObject EventObjectVector::getEarliestObject() const {
	return EO_CAST(TimedObjectVector::getEarliestObject());
}

SPtrEventObject EventObjectVector::getLatestObject() const {
	return EO_CAST(TimedObjectVector::getLatestObject());
}

SPtrEventObject EventObjectVector::getLowerObject(double offset, double unit_scale) {
	return EO_CAST(TimedObjectVector::getLowerObject(offset, unit_scale));
}

SPtrEventObject EventObjectVector::getUpperObject(double offset, double unit_scale) {
	return EO_CAST(TimedObjectVector::getUpperObject(offset, unit_scale));
}
