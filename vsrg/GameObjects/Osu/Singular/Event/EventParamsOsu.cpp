#include "stdafx.h"
#include "EventParamsOsu.h"

YAML::Node EventParamsOsu::asYaml() const {
	YAML::Node node;

	node["sample"] = sample_;
	node["sample_index"] = sample_index_;
	node["volume"] = volume_;
	node["is_kiai"] = is_kiai_;

	return node;
}
