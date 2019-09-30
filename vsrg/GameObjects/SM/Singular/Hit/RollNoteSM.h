#pragma once
#include "BaseObjects/Singular/Hit/LongNote.h"
class RollNoteSM : public LongNote
{
	std::string asNative() const override;
};

