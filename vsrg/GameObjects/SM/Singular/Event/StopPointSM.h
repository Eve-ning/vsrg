#pragma once
#include "BaseObjects/Singular/Event/EventObject.h"

// This doesn't really follow ScrollPoint implementation, so we'll use EventObj
class StopPointSM : public EventObject
{
	StopPointSM(double offset_m_sec, double length, double unit_scale = TimedObject::UnitScale::second);
	
	SPtrTimedObject Clone() const override;

	// Returns =Seconds
	std::string asNative() const override;

	StopPointSM(double offset_m_sec, double length_m_sec);

	double getLength(double unit_scale = TimedObject::UnitScale::second) const;
	void setLength(double length, double unit_scale = TimedObject::UnitScale::second);
	double getEnd(double unit_scale = TimedObject::UnitScale::second) const;
	void setEnd(double end, double unit_scale = TimedObject::UnitScale::second);

	bool isValid() const override;

private:
	double length_m_sec_; // Despite natively, in seconds, we use m_sec to be consistent
};

