#include "stdafx.h"
#include "HitObject.h"

HitObject::HitObject(const double & offset_m_sec,
					 const int & index) :
	TimedObject(offset_m_sec), index_(index) {}
HitObject::~HitObject() {}

std::string HitObject::getInfo() const {
	return TimedObject::getInfo() +
		   "Index " + std::to_string(index_) + '\n';
}

bool HitObject::isValid() const {
	// Put in index validation if required.
	return TimedObject::isValid() && index_ > 0;
}

int HitObject::getIndex() const {
	return index_;
}
void HitObject::setIndex(const int & index) {
	index_ = index;
}

bool HitObject::isOverlapping(const std::shared_ptr<HitObject>& ho) const
{
	return (getOffset() == ho->getOffset()) &&
		   (getIndex() == ho->getIndex());
}
