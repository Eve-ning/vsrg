#pragma once
#include "VsrgMapParams.h"
class VsrgMapOsuParams : VsrgMapParams
{
public:
	VsrgMapOsuParams();
	~VsrgMapOsuParams();

private:
	double hp;
	double od;
	unsigned int keys;
};

