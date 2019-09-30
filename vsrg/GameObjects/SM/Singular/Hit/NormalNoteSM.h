#pragma once
#include "BaseObjects/Singular/Hit/NormalNote.h"
class NormalNoteSM : public NormalNote
{
	NormalNoteSM() {}

	std::string asNative() const override;
	// There shouldn't be any need for extra implementation other than
	// exporting w.r.t. pure virtuals
};

