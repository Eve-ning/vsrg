#pragma once
#include "BaseObjects/Singular/Event/EventObject.h"
class StopPointSM : public EventObject
{
	std::string asNative() const override;
};

