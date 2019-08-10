#include "stdafx.h"
#include "TimedObject.h"

const double TimedObject::hour_to_m_sec = 3600000.0;
const double TimedObject::min_to_m_sec = 60000.0;
const double TimedObject::sec_to_m_sec = 1000.0;

TimedObject::TimedObject(double offset_ms) : offset_m_sec_(offset_ms) {}
TimedObject::~TimedObject() {}

double TimedObject::getOffsetMSec() const {
	return offset_m_sec_;
}

double TimedObject::getOffsetSec() const {
	return offset_m_sec_ / sec_to_m_sec;
}

double TimedObject::getOffsetMin() const {
	return offset_m_sec_ / min_to_m_sec;
}

double TimedObject::getOffsetHour() const {
	return offset_m_sec_ / hour_to_m_sec;
}

void TimedObject::setOffsetMSec(const double & offset_m_sec) {
	offset_m_sec_ = offset_m_sec;
}

void TimedObject::setOffsetSec(const double & offset_sec) {
	offset_m_sec_ = offset_sec * sec_to_m_sec;
}

void TimedObject::setOffsetMin(const double & offset_min) {
	offset_m_sec_ = offset_min * min_to_m_sec;
}

void TimedObject::setOffsetHour(const double & offset_hour) {
	offset_m_sec_ = offset_hour * hour_to_m_sec;
}

bool TimedObject::isValid() const {
	return offset_m_sec_ >= 0.0;
}

TimedObject::operator bool() const
{
	return isValid();
}

std::string TimedObject::getInfo() const
{
	return "Offset " + std::to_string(offset_m_sec_) + '\n';
}

TimedObject::operator std::string() const {
	return getInfo();
}

bool TimedObject::operator==(const TimedObject & obj) const
{
	return getOffsetMSec() == obj.getOffsetMSec();
}

SPtrTimedObject TimedObject::operator*(double by_ms) const {
	SPtrTimedObject to = Clone(); to->setOffsetMSec(to->getOffsetMSec() * by_ms); return to;
}
SPtrTimedObject TimedObject::operator/(double by_ms) const {
	SPtrTimedObject to = Clone(); to->setOffsetMSec(to->getOffsetMSec() / by_ms); return to;
}
SPtrTimedObject TimedObject::operator+(double by_ms) const {
	SPtrTimedObject to = Clone(); to->setOffsetMSec(to->getOffsetMSec() + by_ms); return to;
}
SPtrTimedObject TimedObject::operator-(double by_ms) const {
	SPtrTimedObject to = Clone(); to->setOffsetMSec(to->getOffsetMSec() - by_ms); return to;
}
void TimedObject::operator*=(double by_ms) {
	setOffsetMSec(getOffsetMSec() * by_ms);
}
void TimedObject::operator/=(double by_ms) {
	setOffsetMSec(getOffsetMSec() / by_ms);
}
void TimedObject::operator+=(double by_ms) {
	setOffsetMSec(getOffsetMSec() + by_ms);
}
void TimedObject::operator-=(double by_ms) {
	setOffsetMSec(getOffsetMSec() - by_ms);
}