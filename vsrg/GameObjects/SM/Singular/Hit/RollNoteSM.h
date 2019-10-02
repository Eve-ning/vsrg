#pragma once
#include "BaseObjects/Singular/Hit/LongNote.h"
class RollNoteSM : public LongNote
{
	using LongNote::LongNote;
	SPtrTimedObject Clone() const override;

	std::string asNative() const override;
};

