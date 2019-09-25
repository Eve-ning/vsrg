#include "stdafx.h"
#include "NormalNoteOsu.h"
#include "Helpers/MiscHelper.h"

NormalNoteOsu::NormalNoteOsu(const double & offset_m_sec, const int & index) :
	NormalNote(offset_m_sec, index) {}

NormalNoteOsu::NormalNoteOsu(const std::string & str, int keys) {

	auto tokens = IterHelper::tokenize(str, ",:", 10U);
	auto it = tokens.cbegin();
	
	try {
		/* 0 */		  setIndex(HitParamsOsu::axisToIndex(std::stod(*it), keys));
		/* 1 */ it++; 															
		/* 2 */ it++; setOffset(std::stod(*it));								
		/* 3 */ it++; 															
		/* 4 */ it++; params.hitsound_		= std::stoul(*it);				
		/* 5 */ it++; params.sample_		= std::stoul(*it);			
		/* 6 */ it++; params.addition_		= std::stoul(*it);				
		/* 7 */ it++; params.custom_		= std::stoul(*it);			
		/* 8 */ it++; params.volume_		= std::stoul(*it);			
		/* 9 */ it++; params.hitsound_file_	= *it;							
	}
	catch ([[maybe_unused]] std::out_of_range &e) {
		throw std::exception("Normal Note has a bad format");
	}
}

std::string NormalNoteOsu::asNative(int keys) const {
	std::string out = "";
	out +=  std::to_string(HitParamsOsu::indexToAxis(getIndex(), keys)) +
		',' + "192" +
		',' + std::to_string(getOffset()) +
		',' + "1" +
		',' + std::to_string(params.hitsound_) +
		',' + std::to_string(params.sample_) +
		':' + std::to_string(params.addition_) +
		':' + std::to_string(params.custom_) +
		':' + std::to_string(params.volume_) +
		':' + params.hitsound_file_;
	return std::move(out);
}

std::string NormalNoteOsu::asNative() const {
	// This is a default override for asNative, keys should have been provided
	return asNative(0);
}

NormalNoteOsu::~NormalNoteOsu(){}

SPtrTimedObject NormalNoteOsu::Clone() const {
	return std::make_shared<NormalNoteOsu>(*this);
}