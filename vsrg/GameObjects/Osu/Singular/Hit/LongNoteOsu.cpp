#include "stdafx.h"
#include "LongNoteOsu.h"
#include "HitParamsOsu.h"
#include "Helpers/MiscHelper.h"

LongNoteOsu::LongNoteOsu() {}
LongNoteOsu::LongNoteOsu(double offset_m_sec, unsigned int index, double length) :
	LongNote(offset_m_sec, index, length) {}

LongNoteOsu::LongNoteOsu(const std::string & str, int keys) {
	
	auto it = IterHelper::tokenize_(str, ",:").begin();

	double offset;
	double offset_end;
	try {
		/* 0  */       setIndex(HitParamsOsu::axisToIndex(std::stod(*it), keys));
		/* 1  */ it++; 
		/* 2  */ it++; offset = std::stod(*it);
		/* 3  */ it++; 
		/* 4  */ it++; params.hitsound_		 = std::stoi(*it);
		/* 5  */ it++; offset_end			 = std::stod(*it);
		/* 6  */ it++; params.sample_		 = std::stoi(*it);
		/* 7  */ it++; params.addition_		 = std::stoi(*it);
		/* 8  */ it++; params.custom_		 = std::stoi(*it);
		/* 9  */ it++; params.volume_		 = std::stoi(*it);
		/* 10 */ it++; params.hitsound_file_ = *it;
		setOffset(offset);
		setLength(offset_end - offset);
	}			 
	
	catch ([[maybe_unused]] std::out_of_range &e) {
		throw std::exception("Long Note has a bad format");
	}
}

YAML::Node LongNoteOsu::asYaml() const {
	auto node = LongNote::asYaml();
	node["params"] = params.asYaml();
	return std::move(node);
}
