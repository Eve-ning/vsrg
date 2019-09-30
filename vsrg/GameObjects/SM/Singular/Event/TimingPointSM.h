#pragma once
#include "BaseObjects/Singular/Event/TimingPoint.h"
class TimingPointSM : public TimingPoint
{
	std::string asNative() const override;
};

