#include "stdafx.h"
#include "ScrollPoint.h"
#include "Helpers/MiscHelper.h"

/**
* @brief Construct a new Scroll Point object
*
* @param offset_m_sec Offset in Milliseconds
* @param scroll_speed_mult Scroll Speed multiplier. 1.0 is the base multiplier
*/

ScrollPoint::ScrollPoint() : scroll_mult_(1.0) {}

ScrollPoint::ScrollPoint(double offset_m_sec, double scroll_speed_mult) :
	EventObject(offset_m_sec),
	scroll_mult_(scroll_speed_mult) {}
ScrollPoint::ScrollPoint(const YAML::Node & node) {
	fromYaml(node);
}
ScrollPoint::~ScrollPoint() {}

std::string ScrollPoint::getYamlTag() const {
	return "scroll_point";
}

double ScrollPoint::getScrollSpeedMult() const {
	return scroll_mult_;
}
void ScrollPoint::setScrollSpeedMult(double scroll_speed_mult) {
	scroll_mult_ = scroll_speed_mult;
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

YAML::Node ScrollPoint::asYaml() const {
	auto out = EventObject::asYaml();
	out["scroll_mult"] = StringHelper::formatDbl(scroll_mult_);
	return out;
}

void ScrollPoint::fromYaml(const YAML::Node & node){
	EventObject::fromYaml(node);
	scroll_mult_ = node["scroll_mult"].as<double>();
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
SPtrScrollPoint ScrollPoint::operator*(double by) const {
	SPtrScrollPoint to = std::static_pointer_cast<ScrollPoint>(Clone());
	to->setScrollSpeedMult(getScrollSpeedMult() * by); return to;
}
SPtrScrollPoint ScrollPoint::operator/(double by) const {
	SPtrScrollPoint to = std::static_pointer_cast<ScrollPoint>(Clone());
	to->setScrollSpeedMult(getScrollSpeedMult() / by); return to;
}
SPtrScrollPoint ScrollPoint::operator+(double by) const {
	SPtrScrollPoint to = std::static_pointer_cast<ScrollPoint>(Clone());
	to->setScrollSpeedMult(getScrollSpeedMult() + by); return to;
}
SPtrScrollPoint ScrollPoint::operator-(double by) const{
	SPtrScrollPoint to = std::static_pointer_cast<ScrollPoint>(Clone());
	to->setScrollSpeedMult(getScrollSpeedMult() - by); return to;
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

