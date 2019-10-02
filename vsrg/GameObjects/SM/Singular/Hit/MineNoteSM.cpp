#include "stdafx.h"
#include "MineNoteSM.h"

MineNoteSM::MineNoteSM() {}

SPtrTimedObject MineNoteSM::Clone() const {
	return std::make_shared<MineNoteSM>(*this);
}

std::string MineNoteSM::asNative() const {
	return "M";
}
