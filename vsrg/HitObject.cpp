#include "stdafx.h"
#include "HitObject.h"

HitObject::HitObject(const double & offset_m_sec,
					 const int & column,
					 const int & starts_from) :
	TimedObject(offset_m_sec) {
	setColumn(column, starts_from);
}

HitObject::~HitObject()
{
}

std::string HitObject::getInfo() const {
	return TimedObject::getInfo() +
		"Column " + std::to_string(column_) + '\n';
}

bool HitObject::operator==(const HitObject & ho) const
{
	return (getOffsetMSec() == ho.getOffsetMSec()) &&
		(getColumn() == ho.getColumn());
}

bool HitObject::isValid() const {
	// Put in column validation if required.
	return TimedObject::isValid() && column_ > 0;
}

int HitObject::getColumn(const int & starts_from) const {
	return column_ + starts_from;
}

void HitObject::setColumn(const int & column, const int & starts_from) {
	column_ = column - starts_from;
}

bool HitObject::isOverlapping(const HitObject & ho) const
{
	return (this->operator==(ho));
}
