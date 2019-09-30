#pragma once
#include "BaseObjects/Singular/Hit/LongNote.h"
class HoldNoteSM : public LongNote
{
	HoldNoteSM() {}

	std::string asNative() const override;
	// There shouldn't be any need for extra implementation other than
	// exporting w.r.t. pure virtuals
};

