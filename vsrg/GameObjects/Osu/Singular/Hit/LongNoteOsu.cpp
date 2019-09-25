#include "stdafx.h"
#include "LongNoteOsu.h"
#include "HitParamsOsu.h"
#include "Helpers/MiscHelper.h"

LongNoteOsu::LongNoteOsu() {}
LongNoteOsu::LongNoteOsu(double offset_m_sec, unsigned int index, double length) :
	LongNote(offset_m_sec, index, length) {}

LongNoteOsu::LongNoteOsu(const std::string & str, int keys) {
	
	auto tokens = IterHelper::tokenize(str, ",:", 11U);
	auto it = tokens.cbegin();

	double offset;
	double offset_end;
	try {
		/* 0  */       setIndex(HitParamsOsu::axisToIndex(std::stod(*it), keys));
		/* 1  */ it++; 
		/* 2  */ it++; offset = std::stod(*it);
		/* 3  */ it++; 
		/* 4  */ it++; params.hitsound_		 = std::stoul(*it);
		/* 5  */ it++; offset_end			 = std::stod(*it);
		/* 6  */ it++; params.sample_		 = std::stoul(*it);
		/* 7  */ it++; params.addition_		 = std::stoul(*it);
		/* 8  */ it++; params.custom_		 = std::stoul(*it);
		/* 9  */ it++; params.volume_		 = std::stoul(*it);
		/* 10 */ it++; params.hitsound_file_ = *it;
		setOffset(offset);
		setLength(offset_end - offset);
	}			 
	
	catch ([[maybe_unused]] std::out_of_range &e) {
		throw std::exception("Long Note has a bad format");
	}
}

LongNoteOsu::~LongNoteOsu() {}

SPtrTimedObject LongNoteOsu::Clone() const {
	return std::make_shared<LongNoteOsu>(*this);
}

std::string LongNoteOsu::asNative(int keys) const
{
	std::string out = "";
	out += std::to_string(HitParamsOsu::indexToAxis(getIndex(), keys)) +
		',' + "192" +
		',' + std::to_string(getOffset()) +
		',' + "128" +
		',' + std::to_string(params.hitsound_) +
		',' + std::to_string(getOffsetEnd()) +
		':' + std::to_string(params.sample_) +
		':' + std::to_string(params.addition_) +
		':' + std::to_string(params.custom_) +
		':' + std::to_string(params.volume_) +
		':' + params.hitsound_file_;
	return std::move(out);
}

std::string LongNoteOsu::asNative() const
{
	return asNative(0);
}

