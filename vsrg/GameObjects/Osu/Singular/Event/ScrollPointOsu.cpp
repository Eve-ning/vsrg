#include "stdafx.h"
#include "ScrollPointOsu.h"
#include "Helpers/MiscHelper.h"

ScrollPointOsu::ScrollPointOsu(double offset_m_sec, double scroll_speed_mult) :
	ScrollPoint(offset_m_sec, scroll_speed_mult), params(){}

ScrollPointOsu::ScrollPointOsu(const std::string & str) {
	auto tokens = IterHelper::tokenize(str, ",", 8U);
	auto it = tokens.cbegin();

	/* 0 */       setOffset(std::stod(*it));
	/* 1 */ it++; setScrollSpeedMult(-100.0 / std::stod(*it));
	/* 2 */ it++;
	/* 3 */ it++; params.sample_ = std::stoul(*it);
	/* 4 */ it++; params.sample_index_ = std::stoul(*it);
	/* 5 */ it++; params.volume_ = std::stoul(*it);
	/* 6 */ it++;
	/* 7 */ it++; params.is_kiai_ = (*it == "1");
}

ScrollPointOsu::~ScrollPointOsu()
{
}

std::string ScrollPointOsu::asNative() const {
	std::string out = "";
	out += std::to_string(getOffset()) +
		',' + std::to_string(-100.0 / getScrollSpeedMult()) +
		',' + '4' + 
		',' + std::to_string(params.sample_) +
		',' + std::to_string(params.sample_index_) +
		',' + std::to_string(params.volume_) +
		',' + '0' +
		',' + (params.is_kiai_ ? '1' : '0');
	return std::move(out);
}

YAML::Node ScrollPointOsu::asYaml() const {
	auto node = ScrollPoint::asYaml();
	node["params"] = params.asYaml();
	return std::move(node);
}

void ScrollPointOsu::fromYaml(const YAML::Node& node) {
	ScrollPoint::fromYaml(node);
	params.fromYaml(node);
}
