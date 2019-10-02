#pragma once
#include "BaseObjects/Singular/Hit/NormalNote.h"

// Despite it being a mine, we classify it as a note for convenience
class MineNoteSM : public NormalNote
{
	using NormalNote::NormalNote;
	SPtrTimedObject Clone() const override;

	std::string asNative() const override;
};

