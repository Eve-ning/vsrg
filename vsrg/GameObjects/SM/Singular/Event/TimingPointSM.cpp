#include "stdafx.h"
#include "TimingPointSM.h"

std::string TimingPointSM::asNative() const {
	return "=" + std::to_string(getBpm());
}
