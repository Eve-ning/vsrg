#pragma once
#include "TimedObjectVector.h"
#include "EventObject.h"
class EventObjectVector : public TimedObjectVector
{
public:
	EventObjectVector() : eo_v_({}) {}

	~EventObjectVector();

	std::vector<SPtrEventObject> getEventObjectVector() const;
	void setEventObjectVector(std::vector<SPtrEventObject> eo_v);
private:
	std::vector<SPtrEventObject> eo_v_;
};
