#include "stdafx.h"
#include "NormalNoteSM.h"

SPtrTimedObject NormalNoteSM::Clone() const {
	return std::make_shared<NormalNoteSM>(*this);
}

std::string NormalNoteSM::asNative() const {
	return "1";
}
