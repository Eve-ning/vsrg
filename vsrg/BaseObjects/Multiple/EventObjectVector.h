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
};
