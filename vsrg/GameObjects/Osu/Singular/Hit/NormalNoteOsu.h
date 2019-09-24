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
	using NormalNote::NormalNote;
	~NormalNoteOsu();

	YAML::Node asYaml() const override;
	void fromYaml(const YAML::Node& node) override;
	std::string asNative(int keys) const override;
	std::string asNative() const override;

	HitParamsOsu params;
};

