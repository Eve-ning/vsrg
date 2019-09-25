#include "stdafx.h"
#include "EventObjectVectorOsu.h"
#include "GameObjects/Osu/Singular/Event/ScrollPointOsu.h"
#include "GameObjects/Osu/Singular/Event/TimingPointOsu.h"

EventObjectVectorOsu::EventObjectVectorOsu()
{
}

EventObjectVectorOsu::~EventObjectVectorOsu()
{
}

void EventObjectVectorOsu::fromYaml(const YAML::Node & node) {
	for (const auto & entry : node["timing_point"])
		to_v_.push_back(std::make_shared<TimingPointOsu>(TimingPointOsu(entry)));
	for (const auto & entry : node["scroll_point"])
		to_v_.push_back(std::make_shared<ScrollPointOsu>(ScrollPointOsu(entry)));
}
