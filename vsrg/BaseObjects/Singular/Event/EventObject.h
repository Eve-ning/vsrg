#pragma once
#include "BaseObjects/Singular/TimedObject.h"

/**
 * @brief A counterpart to HitObject, this acts as an abstract class that non-hittable objects inherit from.
 * 
 * This doesn't have any special attributes for now
 */
class EventObject : public TimedObject
{
public:
	EventObject();
	EventObject(double offset_m_sec);
	~EventObject() = 0;
};

typedef std::shared_ptr<EventObject> SPtrEventObject;