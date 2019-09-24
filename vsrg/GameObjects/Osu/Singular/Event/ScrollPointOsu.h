#pragma once
#include "BaseObjects/Singular/Event/ScrollPoint.h"
#include "EventParamsOsu.h"
class ScrollPointOsu :
	public ScrollPoint
{
public:
	ScrollPointOsu(double offset_m_sec, double scroll_speed_mult);
	ScrollPointOsu(const std::string & str);
	using ScrollPoint::ScrollPoint;
	~ScrollPointOsu();

	EventParamsOsu params;

	std::string asNative() const override;

	YAML::Node asYaml() const override;
	void fromYaml(const YAML::Node& node) override;
};

