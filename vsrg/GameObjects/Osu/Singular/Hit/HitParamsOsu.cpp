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

	return node;
}
