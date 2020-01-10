#pragma once
#include "BaseObjects/Singular/Hit/LongNote.h"
class HoldNoteSM : public LongNote
{
	using LongNote::LongNote;
	SPtrTimedObject Clone() const override;

	std::string asNative() const override;
public:
	static constexpr char chr_head = '2';
	static constexpr char chr_tail = '3';
};

