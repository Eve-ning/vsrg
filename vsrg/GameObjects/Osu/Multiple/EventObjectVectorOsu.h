#pragma once
#include "BaseObjects/Multiple/EventObjectVector.h"
class EventObjectVectorOsu :
	public EventObjectVector
{
public:
	EventObjectVectorOsu();
	~EventObjectVectorOsu();

	void fromYaml(const YAML::Node & node) override;
};

