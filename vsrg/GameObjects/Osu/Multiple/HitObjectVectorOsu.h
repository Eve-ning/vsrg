#pragma once
#include "BaseObjects/Multiple/HitObjectVector.h"
class HitObjectVectorOsu :
	public HitObjectVector
{
public:
	HitObjectVectorOsu();
	~HitObjectVectorOsu();

	void fromYaml(const YAML::Node & node) override;
};

