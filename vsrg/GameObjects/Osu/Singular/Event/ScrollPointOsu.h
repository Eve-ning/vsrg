#pragma once
#include "BaseObjects/Singular/Event/ScrollPoint.h"
#include "EventParamsOsu.h"
class ScrollPointOsu :
	public ScrollPoint
{
public:
	ScrollPointOsu(double offset_m_sec, double scroll_speed_mult);
	ScrollPointOsu(const std::string & str);
	~ScrollPointOsu();
	using ScrollPoint::ScrollPoint;
	SPtrTimedObject Clone() const override;

	EventParamsOsu params;

	std::string asNative() const override;
};

