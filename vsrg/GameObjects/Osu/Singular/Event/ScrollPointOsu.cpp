#include "stdafx.h"
#include "ScrollPointOsu.h"


ScrollPointOsu::ScrollPointOsu(double offset_m_sec, double scroll_speed_mult) :
	ScrollPoint(offset_m_sec, scroll_speed_mult) {}

ScrollPointOsu::ScrollPointOsu(const std::string & str) {
	std::vector<std::string> str_v;
	boost::split(str_v, str, boost::is_any_of(','));

	setOffset(std::stod(str_v[0]));
	setScrollSpeedMult(-100.0 / std::stod(str_v[1]));
	params.sample_ = std::stoi(str_v[3]);
	params.sample_index_ = std::stoi(str_v[4]);
	params.volume_ = std::stoi(str_v[5]);
	params.is_kiai_ = (str_v[7] == "1");
}

ScrollPointOsu::~ScrollPointOsu()
{
}
