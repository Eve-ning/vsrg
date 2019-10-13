#include "stdafx.h"
#include "RollNoteSM.h"

SPtrTimedObject RollNoteSM::Clone() const {
	return std::make_shared<RollNoteSM>(*this);
}

std::string RollNoteSM::asNative() const {
	return "";
}
