#include "stdafx.h"
#include "TimedObject.h"
#include "Helpers/MiscHelper.h"

const double TimedObject::Units::hour = 3600000.0;
const double TimedObject::Units::minute = 60000.0;
const double TimedObject::Units::second = 1000.0;
const double TimedObject::Units::msecond = 1.0;
inline double TimedObject::Units::bpmToMspb(const double& bpm) {
	return 1.0 * minute / bpm;
}

double TimedObject::SNAP_ERROR_MARGIN = 0.1;

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

std::string TimedObject::asNative(int keys) const {
	return "";
}

bool TimedObject::operator==(const TimedObject & obj) const { return getOffset() == obj.getOffset(); }
bool TimedObject::operator> (const TimedObject & obj) const { return getOffset() > obj.getOffset(); }
bool TimedObject::operator< (const TimedObject & obj) const { return getOffset() < obj.getOffset(); }
bool TimedObject::operator<=(const TimedObject & obj) const { return getOffset() >= obj.getOffset(); }
bool TimedObject::operator>=(const TimedObject & obj) const { return getOffset() <= obj.getOffset(); }
bool TimedObject::operator> (const double & offset_m_sec) const	{ return offset_m_sec_ >  offset_m_sec; }
bool TimedObject::operator< (const double & offset_m_sec) const	{ return offset_m_sec_ <  offset_m_sec; }
bool TimedObject::operator<=(const double & offset_m_sec) const	{ return offset_m_sec_ <= offset_m_sec; }
bool TimedObject::operator>=(const double & offset_m_sec) const	{ return offset_m_sec_ >= offset_m_sec; }
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
void TimedObject::operator*=(double by_m_sec) { setOffset(getOffset() * by_m_sec); }
void TimedObject::operator/=(double by_m_sec) { setOffset(getOffset() / by_m_sec); }
void TimedObject::operator+=(double by_m_sec) { setOffset(getOffset() + by_m_sec); }
void TimedObject::operator-=(double by_m_sec) { setOffset(getOffset() - by_m_sec); }
