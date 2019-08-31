#include "stdafx.h"
#include "LongNoteOsu.h"
#include "HitParamsOsu.h"

LongNoteOsu::LongNoteOsu() {}
LongNoteOsu::LongNoteOsu(double offset_m_sec, unsigned int index, double length) :
	LongNote(offset_m_sec, index, length) {}

LongNoteOsu::LongNoteOsu(const std::string & str, int keys) {
	std::vector<std::string> str_v;
	std::string delimiters(",:");
	boost::split(str_v, str, boost::is_any_of(delimiters));

	try {
		setIndex(HitParamsOsu::axisToIndex(std::stod(str_v[0]), keys));
		double offset = std::stod(str_v[2]);
		double offset_end = std::stod(str_v[5]);
		setOffset(offset);
		setLength(offset_end - offset);

		params.hitsound_ = std::stoi(str_v[4]);
		params.sample_ = std::stoi(str_v[6]);
		params.addition_ = std::stoi(str_v[7]);
		params.custom_ = std::stoi(str_v[8]);
		params.volume_ = std::stoi(str_v[9]);
		params.hitsound_file_ = str_v[10];
	}
	
	catch ([[maybe_unused]] std::out_of_range &e) {
		throw std::exception("Long Note has a bad format");
	}
}
