#include "stdafx.h"
#include "StopPointSM.h"

StopPointSM::StopPointSM(double offset_m_sec, double length, double unit_scale) :
	EventObject(offset_m_sec), length_m_sec_(length / unit_scale) {}

inline std::string StopPointSM::asNative() const {
	return "=" + std::to_string(length_m_sec_ * UnitScale::second);
}

double StopPointSM::getLength(double unit_scale) const {
	return length_m_sec_ * unit_scale;
}

void StopPointSM::setLength(double length, double unit_scale) {
	length_m_sec_ = length / unit_scale;
}

double StopPointSM::getEnd(double unit_scale) const {
	return getOffset(unit_scale) + (length_m_sec_ * unit_scale);
}

void StopPointSM::setEnd(double end, double unit_scale) {
	length_m_sec_ = (end / unit_scale) - getOffset(unit_scale);
}

bool StopPointSM::isValid() const {
	return isValid() && (length_m_sec_ > 0);
}
