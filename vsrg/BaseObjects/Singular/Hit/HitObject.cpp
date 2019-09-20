#include "stdafx.h"
#include "HitObject.h"


/**
* @brief Construct a new Hit Object
*
* @param offset_m_sec Offset of the object
* @param index Index of the object
*/

HitObject::HitObject() {}

HitObject::HitObject(const double & offset_m_sec,
					 const int & index) :
	TimedObject(offset_m_sec), index_(index) {}
HitObject::HitObject(const YAML::Node & node) {
	fromYaml(node);
}
HitObject::~HitObject() {}

bool HitObject::isValid() const {
	// Put in index validation if required.
	return TimedObject::isValid() && index_ >= 0;
}

YAML::Node HitObject::toYaml() const {
	auto out = TimedObject::toYaml();
	out["index"] = index_;
	return out;
}

void HitObject::fromYaml(const YAML::Node & node) {
	TimedObject::fromYaml(node);
	index_ = node["index"].as<int>();
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
