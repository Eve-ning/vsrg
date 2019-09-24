#pragma once
struct EventParamsOsu
{
	unsigned int sample_;
	unsigned int sample_index_;
	unsigned int volume_;
	bool is_kiai_;

	YAML::Node asYaml() const;
	void fromYaml(const YAML::Node& node);
};

