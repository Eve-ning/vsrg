#pragma once
#include "BaseObjects/Singular/Hit/NormalNote.h"
#include "HitParamsOsu.h"
class NormalNoteOsu :
	public NormalNote
{
public: 
	NormalNoteOsu(const double & offset_m_sec, 
				  const int & index);
	NormalNoteOsu(const std::string & str, int keys);
	~NormalNoteOsu();

	HitParamsOsu params;
};

