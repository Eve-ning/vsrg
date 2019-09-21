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
};

typedef std::shared_ptr<HitObjectVector> SPtrHitObjectVector;