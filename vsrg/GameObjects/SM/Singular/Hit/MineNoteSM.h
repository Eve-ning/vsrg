#pragma once
#include "BaseObjects/Singular/Hit/NormalNote.h"
class MineNoteSM : public NormalNote
{
	std::string asNative() const override;
};

