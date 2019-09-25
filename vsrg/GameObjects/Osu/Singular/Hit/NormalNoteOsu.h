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
	using NormalNote::NormalNote;
	SPtrTimedObject Clone() const override;

	std::string asNative(int keys) const override;
	std::string asNative() const override;


	HitParamsOsu params;
};

