#include "stdafx.h"
#include "EventParamsOsu.h"

YAML::Node EventParamsOsu::asYaml() const {
	YAML::Node node;

	node["sample"] = sample_;
	node["sample_index"] = sample_index_;
	node["volume"] = volume_;
	node["is_kiai"] = is_kiai_;

	return std::move(node);
}

void EventParamsOsu::fromYaml(const YAML::Node& node) {
	sample_ = node["sample"].as<unsigned int>();
	sample_index_ = node["sample_index"].as<unsigned int>();
	volume_ = node["volume"].as<unsigned int>();
	is_kiai_ = node["is_kiai"].as<bool>();
}
