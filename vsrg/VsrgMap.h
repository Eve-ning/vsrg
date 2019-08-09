#pragma once
#include <vector>
#include "HitObject.h"
#include "TimedObject.h"

typedef std::vector<std::shared_ptr<HitObject>> HOV;
typedef std::vector<std::shared_ptr<TimedObject>> TPV;
class VsrgMap
{
public:
	VsrgMap();
	~VsrgMap();

private:
	HOV ho_v_;
	TPV to_v_;
};

