#pragma once	
#include "BaseObjects/Singular/Event/TimingPoint.h"
class TimingPointSM : public TimingPoint
{
	using TimingPoint::TimingPoint;

	SPtrTimedObject Clone() const override;
	std::string asNative() const override;
};

