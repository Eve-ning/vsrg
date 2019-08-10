#include "stdafx.h" 
#include "EventObjectVector.h"



EventObjectVector::EventObjectVector() : TimedObjectVector() {}

EventObjectVector::~EventObjectVector()
{
}

std::vector<SPtrEventObject> EventObjectVector::getEventObjectVector() const {
	return eo_v_;
}

void EventObjectVector::setEventObjectVector(std::vector<SPtrEventObject> eo_v)
{
	eo_v_ = eo_v;
}
