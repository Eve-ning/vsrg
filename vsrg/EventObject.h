#pragma once
#include "TimedObject.h"

/**
 * @brief A counterpart to HitObject, this acts as an abstract class that non-hittable objects inherit from.
 * 
 * This doesn't have any special attributes for now
 */
class EventObject : public TimedObject
{
public:
	EventObject(double offset_m_sec);
	~EventObject() = 0;
	virtual std::shared_ptr<TimedObject> Clone() const override = 0;
};

typedef std::shared_ptr<EventObject> SPtrEventObject;