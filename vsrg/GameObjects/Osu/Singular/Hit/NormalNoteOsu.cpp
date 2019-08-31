#include "stdafx.h"
#include "NormalNoteOsu.h"

NormalNoteOsu::NormalNoteOsu(const double & offset_m_sec, const int & index) :
	NormalNote(offset_m_sec, index) {}

NormalNoteOsu::NormalNoteOsu(const std::string & str, int keys) {
	std::vector<std::string> str_v;
	std::string delimiters(",:");
	boost::split(str_v, str, boost::is_any_of(delimiters));

	try {
		setIndex(HitParamsOsu::axisToIndex(std::stod(str_v[0]), keys));
		setOffset(std::stod(str_v[2]));

		params.hitsound_		= std::stoi(str_v[4]);
		params.sample_			= std::stoi(str_v[5]);
		params.addition_		= std::stoi(str_v[6]);
		params.custom_			= std::stoi(str_v[7]);
		params.volume_			= std::stoi(str_v[8]);
		params.hitsound_file_	= str_v[9];
	}
	catch ([[maybe_unused]] std::out_of_range &e) {
		throw std::exception("Normal Note has a bad format");
	}
}

NormalNoteOsu::~NormalNoteOsu()
{
}
