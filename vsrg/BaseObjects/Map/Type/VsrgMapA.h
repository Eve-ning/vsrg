#pragma once
#include "BaseObjects/Multiple/HitObjectVector.h"
#include "BaseObjects/Multiple/EventObjectVector.h"
#include "BaseObjects/Map/VsrgMap.h"

// This class handles Vsrg Map formats that are predominantly using millisecond snaps

class VsrgMapA : public VsrgMap
{
public:
	VsrgMapA();
	~VsrgMapA();

	virtual SPtrHitObjectVector getHitObjectVector() const final;
	virtual SPtrEventObjectVector getEventObjectVector() const final;
	virtual void setHitObjectVector(const SPtrHitObjectVector & ho_v) final;
	virtual void setEventObjectVector(const SPtrEventObjectVector & eo_v) final;

protected:

	SPtrHitObjectVector ho_v_;
	SPtrEventObjectVector eo_v_;
};

