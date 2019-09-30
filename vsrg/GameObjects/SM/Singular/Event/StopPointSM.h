#pragma once
#include "BaseObjects/Singular/Event/EventObject.h"

// This doesn't really follow ScrollPoint implementation, so we'll use EventObj
class StopPointSM : public EventObject
{
	StopPointSM(double offset_m_sec, double length);

	std::string asNative() const override;

	double getLength() const;
	void setLength(double length);
	double getEnd() const;
	void setEnd(double end);

	bool isValid() const override;

private:
	double length_;
};

