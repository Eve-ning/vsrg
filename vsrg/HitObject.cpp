#include "stdafx.h"
#include "HitObject.h"

HitObject::HitObject(const double & offset_m_sec,
					 const int & index,
					 const int & starts_from) :
	TimedObject(offset_m_sec) {
	setIndex(index, starts_from);
}

HitObject::~HitObject() {}

std::string HitObject::getInfo() const {
	return TimedObject::getInfo() +
		"Index " + std::to_string(index_) + '\n';
}

bool HitObject::isValid() const {
	// Put in index validation if required.
	return TimedObject::isValid() && index_ > 0;
}

int HitObject::getIndex(const int & starts_from) const {
	return index_ + starts_from;
}

void HitObject::setIndex(const int & index, const int & starts_from) {
	index_ = index - starts_from;
}

bool HitObject::isOverlapping(const std::shared_ptr<HitObject>& ho) const
{
	return (getOffsetMSec() == ho->getOffsetMSec()) &&
		(getIndex() == ho->getIndex());
}
