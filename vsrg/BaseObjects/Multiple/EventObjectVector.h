#pragma once
#include "TimedObjectVector.h"
#include "BaseObjects/Singular/Event/EventObject.h"

class EventObjectVector : public TimedObjectVector
{
public:
	EventObjectVector();
	~EventObjectVector();

	SPtrEventObject operator[](unsigned int index) const;

	std::vector<SPtrEventObject> getEventObjectVector() const;

	SPtrEventObject getEarliestObject() const;
	SPtrEventObject getLatestObject() const;
	SPtrEventObject getLowerObject(double offset, double unit_scale = TimedObject::Units::msecond);
	SPtrEventObject getUpperObject(double offset, double unit_scale = TimedObject::Units::msecond);
};

typedef std::shared_ptr<EventObjectVector> SPtrEventObjectVector;