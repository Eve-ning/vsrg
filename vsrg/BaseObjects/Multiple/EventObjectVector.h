#pragma once
#include "TimedObjectVector.h"
#include "BaseObjects/Singular/Event/EventObject.h"

#define EO_CAST(obj) std::static_pointer_cast<EventObject>(obj)

class EventObjectVector : public TimedObjectVector
{
public:
	EventObjectVector();
	~EventObjectVector();

	SPtrEventObject operator[](unsigned int index) const {
		return EO_CAST(to_v_[index]);
	}

	std::vector<SPtrEventObject> getEventObjectVector() const {
		std::vector<SPtrEventObject> eo_v;
		for (const auto & eo : to_v_) eo_v.push_back(EO_CAST(eo));
		return eo_v;
	}

	SPtrEventObject getEarliestObject() const {
		return EO_CAST(TimedObjectVector::getEarliestObject());
	}
	SPtrEventObject getLatestObject() const {
		return EO_CAST(TimedObjectVector::getLatestObject());
	}
};
