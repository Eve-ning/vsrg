#include "stdafx.h"
#include "ScrollPoint.h"

ScrollPoint::ScrollPoint(double offset_m_sec, double scroll_speed_mult) :
	EventObject(offset_m_sec), scroll_speed_mult_(scroll_speed_mult) {}

ScrollPoint::~ScrollPoint()
{
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
bool ScrollPoint::isApproximately(double value, double threshold, bool include_ends) const {
	if (include_ends) {
		return ((*this >= (value - threshold)) && (*this <= (value + threshold)));
	}
	else {
		return ((*this > (value - threshold)) && (*this < (value + threshold)));
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
ScrollPoint ScrollPoint::operator*(double by) const
{
	return ScrollPoint(getOffsetMSec(), getScrollSpeedMult() * by);
}
ScrollPoint ScrollPoint::operator/(double by) const
{
	return ScrollPoint(getOffsetMSec(), getScrollSpeedMult() / by);
}
ScrollPoint ScrollPoint::operator+(double by) const
{
	return ScrollPoint(getOffsetMSec(), getScrollSpeedMult() + by);
}
ScrollPoint ScrollPoint::operator-(double by) const
{
	return ScrollPoint(getOffsetMSec(), getScrollSpeedMult() - by);
}
void ScrollPoint::operator*=(double by)
{
	setScrollSpeedMult(getScrollSpeedMult() * by);
}
void ScrollPoint::operator/=(double by)
{
	setScrollSpeedMult(getScrollSpeedMult() / by);
}
void ScrollPoint::operator+=(double by)
{
	setScrollSpeedMult(getScrollSpeedMult() + by);
}
void ScrollPoint::operator-=(double by)
{
	setScrollSpeedMult(getScrollSpeedMult() - by);
}