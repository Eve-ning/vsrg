#pragma once
#include "TimedObjectVector.h"
#include "BaseObjects/Singular/Hit/HitObject.h"

class HitObjectVector : public TimedObjectVector
{
public:
	HitObjectVector();
	~HitObjectVector();

	SPtrHitObject operator[](unsigned int index) const;

	std::vector<SPtrHitObject> getHitObjectVector() const;

	SPtrHitObject getEarliestObject() const;
	SPtrHitObject getLatestObject() const;
	SPtrHitObject getLowerObject(double offset, double unit_scale = TimedObject::UnitScale::msecond);
	SPtrHitObject getUpperObject(double offset, double unit_scale = TimedObject::UnitScale::msecond);
};

typedef std::shared_ptr<HitObjectVector> SPtrHitObjectVector;