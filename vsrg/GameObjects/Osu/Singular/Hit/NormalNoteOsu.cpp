#include "stdafx.h"
#include "NormalNoteOsu.h"
#include "Helpers/IterHelper.h"

NormalNoteOsu::NormalNoteOsu(const double & offset_m_sec, const int & index) :
	NormalNote(offset_m_sec, index) {}

NormalNoteOsu::NormalNoteOsu(const std::string & str, int keys) {

	auto it = IterHelper::tokenize(str, ",:").begin();
	
	try {
		/* 0 */		  setIndex(HitParamsOsu::axisToIndex(std::stod(*it), keys));
		/* 1 */ it++; 															
		/* 2 */ it++; setOffset(std::stod(*it));								
		/* 3 */ it++; 															
		/* 4 */ it++; params.hitsound_		= std::stoi(*it);				
		/* 5 */ it++; params.sample_		= std::stoi(*it);			
		/* 6 */ it++; params.addition_		= std::stoi(*it);				
		/* 7 */ it++; params.custom_		= std::stoi(*it);			
		/* 8 */ it++; params.volume_		= std::stoi(*it);			
		/* 9 */ it++; params.hitsound_file_	= *it;							
	}
	catch ([[maybe_unused]] std::out_of_range &e) {
		throw std::exception("Normal Note has a bad format");
	}
}

NormalNoteOsu::~NormalNoteOsu()
{
}
