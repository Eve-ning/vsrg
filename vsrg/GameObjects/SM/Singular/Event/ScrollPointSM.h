#pragma once
#include "BaseObjects/Singular/Event/ScrollPoint.h"
class ScrollPointSM : public ScrollPoint
{
	std::string asNative() const override;
};

