#include "stdafx.h"
#include "TimingPointSM.h"

SPtrTimedObject TimingPointSM::Clone() const {
	return std::make_shared<TimingPointSM>(*this);
}

std::string TimingPointSM::asNative() const {
	return "=" + std::to_string(getBpm());
}
