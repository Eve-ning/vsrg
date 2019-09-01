#include "stdafx.h"
#include "ScrollPointOsu.h"
#include "Helpers/IterHelper.h"

ScrollPointOsu::ScrollPointOsu(double offset_m_sec, double scroll_speed_mult) :
	ScrollPoint(offset_m_sec, scroll_speed_mult) {}

ScrollPointOsu::ScrollPointOsu(const std::string & str) {
	auto it = IterHelper::tokenize(str, ",").begin();

	/* 0 */       setOffset(std::stod(*it));
	/* 1 */ it++; setScrollSpeedMult(-100.0 / std::stod(*it));
	/* 2 */ it++;
	/* 3 */ it++; params.sample_ = std::stoi(*it);
	/* 4 */ it++; params.sample_index_ = std::stoi(*it);
	/* 5 */ it++; params.volume_ = std::stoi(*it);
	/* 6 */ it++;
	/* 7 */ it++; params.is_kiai_ = (*it == "1");
}

ScrollPointOsu::~ScrollPointOsu()
{
}
