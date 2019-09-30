#include "stdafx.h"
#include "StopPointSM.h"

StopPointSM::StopPointSM(double offset_m_sec, double length_sec) :
	EventObject(offset_m_sec), length_sec_(length_sec) {}

inline std::string StopPointSM::asNative() const {
	return "=" + std::to_string(length_sec_);
}

double StopPointSM::getLength() const {
	return length_sec_;
}

void StopPointSM::setLength(double length) {
	length_sec_ = length;
}

double StopPointSM::getEnd() const {
	return getOffset() + length_sec_;
}

void StopPointSM::setEnd(double end) {
	length_sec_ = end - getOffset();
}

bool StopPointSM::isValid() const {
	return isValid() && (length_sec_ > 0);
}
