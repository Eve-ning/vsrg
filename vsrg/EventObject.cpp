#include "stdafx.h"
#include "EventObject.h"

EventObject::EventObject(double offset_m_sec) : TimedObject(offset_m_sec) {}
EventObject::~EventObject() {}

std::string EventObject::getInfo() const {
	return TimedObject::getInfo();
}
