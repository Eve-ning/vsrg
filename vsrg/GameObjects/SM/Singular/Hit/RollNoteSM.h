#pragma once
#include "BaseObjects/Singular/Hit/LongNote.h"
class RollNoteSM : public LongNote
{
	using LongNote::LongNote;
	SPtrTimedObject Clone() const override;

	std::string asNative() const override;
public:
	static constexpr char chr_head = '4';
	static constexpr char chr_tail = '3';
};

