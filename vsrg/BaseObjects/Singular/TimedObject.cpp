#include "stdafx.h"
#include "TimedObject.h"
#include "Helpers/MiscHelper.h"

const double TimedObject::UnitScale::hour = 3600000.0;
const double TimedObject::UnitScale::minute = 60000.0;
const double TimedObject::UnitScale::second = 1000.0;
const double TimedObject::UnitScale::msecond = 1.0;

TimedObject::TimedObject() : offset_m_sec_(0) {}
TimedObject::TimedObject(double offset_m_sec) : offset_m_sec_(offset_m_sec) {}
TimedObject::~TimedObject() {}

double TimedObject::getOffset(double unit_scale) const {
	return offset_m_sec_ / unit_scale;
}

void TimedObject::setOffset(double offset_m_sec, double unit_scale) {
	offset_m_sec_ = offset_m_sec * unit_scale;
}

bool TimedObject::isValid() const {
	return offset_m_sec_ >= 0.0;
}
TimedObject::operator bool() const {
	return isValid();
}

YAML::Node TimedObject::toYaml() const {
	BOOST_ASSERT_MSG(isValid(), "Object must pass isValid() to be exported.");
	YAML::Node out;
	out["offset_m_sec"] = StringHelper::formatDbl(offset_m_sec_);
	return out;
}

void TimedObject::fromYaml(const YAML::Node & node) {
	offset_m_sec_ = node["offset_m_sec"].as<double>();
}

bool TimedObject::operator==(const TimedObject & obj) const {
	return getOffset() == obj.getOffset();
}
bool TimedObject::operator>(const TimedObject & obj) const {
	return getOffset() > obj.getOffset();
}
bool TimedObject::operator<(const TimedObject & obj) const {
	return getOffset() < obj.getOffset();
}
bool TimedObject::operator<=(const TimedObject & obj) const {
	return getOffset() >= obj.getOffset();
}
bool TimedObject::operator>=(const TimedObject & obj) const {
	return getOffset() <= obj.getOffset();
}
std::shared_ptr<TimedObject> TimedObject::operator*(double by_m_sec) const {
	std::shared_ptr<TimedObject> to = Clone(); to->setOffset(to->getOffset() * by_m_sec); return to;
}
std::shared_ptr<TimedObject> TimedObject::operator/(double by_m_sec) const {
	std::shared_ptr<TimedObject> to = Clone(); to->setOffset(to->getOffset() / by_m_sec); return to;
}
std::shared_ptr<TimedObject> TimedObject::operator+(double by_m_sec) const {
	std::shared_ptr<TimedObject> to = Clone(); to->setOffset(to->getOffset() + by_m_sec); return to;
}
std::shared_ptr<TimedObject> TimedObject::operator-(double by_m_sec) const {
	std::shared_ptr<TimedObject> to = Clone(); to->setOffset(to->getOffset() - by_m_sec); return to;
}
void TimedObject::operator*=(double by_m_sec) {
	setOffset(getOffset() * by_m_sec);
}
void TimedObject::operator/=(double by_m_sec) {
	setOffset(getOffset() / by_m_sec);
}
void TimedObject::operator+=(double by_m_sec) {
	setOffset(getOffset() + by_m_sec);
}
void TimedObject::operator-=(double by_m_sec) {
	setOffset(getOffset() - by_m_sec);
}