#include "stdafx.h"
#include "HitObject.h"

/**
* @brief Construct a new Hit Object
*
* @param offset_m_sec Offset of the object
* @param index Index of the object
*/

HitObject::HitObject() : index_(-1) {}

HitObject::HitObject(const double & offset_m_sec,
					 const int & index) :
	TimedObject(offset_m_sec), index_(index) {}
HitObject::~HitObject() {}

bool HitObject::isValid() const {
	// Put in index validation if required.
	return TimedObject::isValid() && index_ >= 0;
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
