#include "stdafx.h"
#include "HitParamsOsu.h"

unsigned int HitParamsOsu::indexToAxis(double index, unsigned int keys) {
	return static_cast<unsigned int>(round(((512 * index) + 256) / keys));
}
unsigned int HitParamsOsu::axisToIndex(double axis, unsigned int keys) {
	return static_cast<unsigned int>(round((axis * keys - 256) / 512));
}

YAML::Node HitParamsOsu::asYaml() const {
	YAML::Node node;

	node["hitsound"] = hitsound_;
	node["sample"] = sample_;
	node["addition"] = addition_;
	node["custom"] = custom_;
	node["volume"] = volume_;
	node["hitsound_file"] = hitsound_file_;

	return std::move(node);
}

void HitParamsOsu::fromYaml(const YAML::Node& node) {
	hitsound_ = node["hitsound"].as<unsigned int>();
	sample_ = node["sample"].as<unsigned int>();
	addition_ = node["addition"].as<unsigned int>();
	custom_ = node["custom"].as<unsigned int>();
	volume_ = node["volume"].as<unsigned int>();
	hitsound_file_ = node["hitsound_file"].as<std::string>();
}
