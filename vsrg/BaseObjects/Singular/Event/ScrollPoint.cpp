#include "stdafx.h"
#include "ScrollPoint.h"


/**
* @brief Construct a new Scroll Point object
*
* @param offset_m_sec Offset in Milliseconds
* @param scroll_speed_mult Scroll Speed multiplier. 1.0 is the base multiplier
*/

ScrollPoint::ScrollPoint() : scroll_speed_mult_(1.0) {}

ScrollPoint::ScrollPoint(double offset_m_sec, double scroll_speed_mult) :
	EventObject(offset_m_sec), scroll_speed_mult_(scroll_speed_mult) {}
ScrollPoint::~ScrollPoint() {}

std::shared_ptr<TimedObject> ScrollPoint::Clone() const {
	return std::make_shared<ScrollPoint>(*this);
}

double ScrollPoint::getScrollSpeedMult() const {
	return scroll_speed_mult_;
}
void ScrollPoint::setScrollSpeedMult(double scroll_speed_mult) {
	scroll_speed_mult_ = scroll_speed_mult;
}

bool ScrollPoint::isNegative(bool include0) const {
	return include0 ? *this <= (0.0) : *this < (0.0);
}
bool ScrollPoint::isPositive(bool include0) const {
	return include0 ? *this >= (0.0) : *this > (0.0);
}
bool ScrollPoint::isApproximately(
	double value,
	double threshold,
	bool include_ends
) const {
	if (include_ends) {
		return ((*this >= (value - threshold)) &&
			    (*this <= (value + threshold)));
	}
	else {
		return ((*this > (value - threshold)) &&
			    (*this < (value + threshold)));
	}
}

bool ScrollPoint::operator>(double value) const {
	return getScrollSpeedMult() > value;
}
bool ScrollPoint::operator<(double value) const {
	return getScrollSpeedMult() < value;
}
bool ScrollPoint::operator>=(double value) const {
	return getScrollSpeedMult() >= value;
}
bool ScrollPoint::operator<=(double value) const {
	return getScrollSpeedMult() <= value;
}
ScrollPoint ScrollPoint::operator*(double by) const {
	return ScrollPoint(getOffset(), getScrollSpeedMult() * by);
}
ScrollPoint ScrollPoint::operator/(double by) const {
	return ScrollPoint(getOffset(), getScrollSpeedMult() / by);
}
ScrollPoint ScrollPoint::operator+(double by) const {
	return ScrollPoint(getOffset(), getScrollSpeedMult() + by);
}
ScrollPoint ScrollPoint::operator-(double by) const{
	return ScrollPoint(getOffset(), getScrollSpeedMult() - by);
}
void ScrollPoint::operator*=(double by) {
	setScrollSpeedMult(getScrollSpeedMult() * by);
}
void ScrollPoint::operator/=(double by) {
	setScrollSpeedMult(getScrollSpeedMult() / by);
}
void ScrollPoint::operator+=(double by) {
	setScrollSpeedMult(getScrollSpeedMult() + by);
}
void ScrollPoint::operator-=(double by) {
	setScrollSpeedMult(getScrollSpeedMult() - by);
}

std::string ScrollPoint::getInfo() const {
	return EventObject::getInfo() +
		"Scroll Speed Mult " + std::to_string(scroll_speed_mult_) + '\n';
}
