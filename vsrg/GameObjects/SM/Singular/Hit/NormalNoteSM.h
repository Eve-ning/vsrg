#pragma once
#include "BaseObjects/Singular/Hit/NormalNote.h"
class NormalNoteSM : public NormalNote
{
	using NormalNote::NormalNote;
	SPtrTimedObject Clone() const override;

	std::string asNative() const override;
public:
	static constexpr char chr = '1';
};

