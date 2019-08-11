#pragma once
#include <vector>
#include "HitObjectVector.h"
#include "EventObjectVector.h"

class VsrgMap
{
public:
	VsrgMap();
	~VsrgMap();
	


private:
	HitObjectVector ho_v_;
	EventObjectVector to_v_;
	
};

