#pragma once
#include "BaseObjects/Singular/Hit/LongNote.h"
#include "HitParamsOsu.h"
class LongNoteOsu :
	public LongNote
{
public:

	LongNoteOsu();
	LongNoteOsu(double offset_m_sec, unsigned int index, double length);
	LongNoteOsu(const std::string & str, int keys);

	HitParamsOsu params;
};

