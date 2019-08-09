#pragma once
#include <vector>
#include "HitObject.h"
#include "TimedObject.h"
class VsrgMap
{
public:
	VsrgMap();
	~VsrgMap();

private:
	std::vector<std::shared_ptr<HitObject>> ho_v_;
	std::vector<std::shared_ptr<TimedObject>> to_v_;
};

