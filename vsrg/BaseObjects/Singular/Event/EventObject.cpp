#include "stdafx.h"
#include "EventObject.h"

EventObject::EventObject() {}
EventObject::EventObject(double offset_m_sec) : TimedObject(offset_m_sec) {}
EventObject::EventObject(const YAML::Node & node) {
	fromYaml(node);
}
EventObject::~EventObject() {}
