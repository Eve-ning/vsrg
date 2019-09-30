#include "stdafx.h"
#include "StopPointSM.h"

StopPointSM::StopPointSM(double offset_m_sec, double length) :
	EventObject(offset_m_sec), length_(length) {}

double StopPointSM::getLength() const {
	return length_;
}

void StopPointSM::setLength(double length) {
	length_ = length;
}

double StopPointSM::getEnd() const {
	return getOffset() + length_;
}

void StopPointSM::setEnd(double end) {
	length_ = end - getOffset();
}

bool StopPointSM::isValid() const {
	return isValid() && (length_ > 0);
}
