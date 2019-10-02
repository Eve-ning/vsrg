#include "stdafx.h"
#include "HoldNoteSM.h"

SPtrTimedObject HoldNoteSM::Clone() const {
	return std::make_shared<HoldNoteSM>(*this);
}

std::string HoldNoteSM::asNative() const {
	return "2";
}
