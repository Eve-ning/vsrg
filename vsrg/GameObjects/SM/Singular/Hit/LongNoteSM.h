#pragma once
#include "BaseObjects/Singular/Hit/LongNote.h"
class LongNoteSM : public LongNote
{
	LongNoteSM() {}

	std::string asNative() const override;
	// There shouldn't be any need for extra implementation other than
	// exporting w.r.t. pure virtuals
};

