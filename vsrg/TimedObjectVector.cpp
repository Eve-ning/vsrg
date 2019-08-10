#include "stdafx.h"
#include "TimedObjectVector.h"

TimedObjectVector::~TimedObjectVector() {}

std::vector<SPtrTimedObject>::iterator TimedObjectVector::begin() { return to_v_.begin(); }
std::vector<SPtrTimedObject>::iterator TimedObjectVector::end()   { return to_v_.end();   }
std::vector<SPtrTimedObject>::const_iterator TimedObjectVector::cbegin() { return to_v_.cbegin(); }
std::vector<SPtrTimedObject>::const_iterator TimedObjectVector::cend() { return to_v_.cend(); }

SPtrTimedObject TimedObjectVector::getTimedObject(unsigned int index) const {
	return to_v_.at(index);
}

SPtrTimedObject TimedObjectVector::operator[](unsigned int index) const {
	return getTimedObject(index);
}

void TimedObjectVector::push_back(SPtrTimedObject to) {
	to_v_.push_back(to);
}

void TimedObjectVector::pop_back() {
	to_v_.pop_back();
}

void TimedObjectVector::clear() {
	to_v_.clear();
}

bool TimedObjectVector::isEmpty() {
	return to_v_.size() == 0;
}

size_t TimedObjectVector::size() const {
	return to_v_.size();
}

std::vector<double> TimedObjectVector::getOffsetHourVector(bool sort) const {
	return getOffsetXVector(sort, TimedObject::hour_to_m_sec);
}
std::vector<double> TimedObjectVector::getOffsetMinVector(bool sort) const {
	return getOffsetXVector(sort, TimedObject::min_to_m_sec);
}
std::vector<double> TimedObjectVector::getOffsetSecVector(bool sort) const {
	return getOffsetXVector(sort, TimedObject::sec_to_m_sec);
}
std::vector<double> TimedObjectVector::getOffsetMSecVector(bool sort) const {
	return getOffsetXVector(sort, 1.0);
}

std::vector<SPtrTimedObject> TimedObjectVector::getTimedObjectVector() const {
	return to_v_;
}

void TimedObjectVector::setTimedObjectVector(const std::vector<SPtrTimedObject>& to_v) {
	to_v_ = to_v;
}

void TimedObjectVector::multiplyOffsetMSec(double offset_m_sec) {
	std::transform(begin(), end(), begin(),
		[offset_m_sec](SPtrTimedObject & to) -> SPtrTimedObject { to->operator*=(offset_m_sec); return to; });
}

void TimedObjectVector::divideOffsetMSec(double offset_m_sec) {
	std::transform(begin(), end(), begin(),
		[offset_m_sec](SPtrTimedObject & to) -> SPtrTimedObject { to->operator/=(offset_m_sec); return to; });
}

void TimedObjectVector::addOffsetMSec(double offset_m_sec) {
	std::transform(begin(), end(), begin(),
		[offset_m_sec](SPtrTimedObject & to) -> SPtrTimedObject { to->operator+=(offset_m_sec); return to; });
}

void TimedObjectVector::subtractOffsetMSec(double offset_m_sec) {
	std::transform(begin(), end(), begin(),
		[offset_m_sec](SPtrTimedObject & to) -> SPtrTimedObject { to->operator-=(offset_m_sec); return to; });
}

void TimedObjectVector::operator*=(double offset_m_sec) { multiplyOffsetMSec(offset_m_sec); }
void TimedObjectVector::operator/=(double offset_m_sec) { divideOffsetMSec(offset_m_sec);   }
void TimedObjectVector::operator+=(double offset_m_sec) { addOffsetMSec(offset_m_sec);      }
void TimedObjectVector::operator-=(double offset_m_sec) { subtractOffsetMSec(offset_m_sec); }

std::vector<double> TimedObjectVector::getOffsetXVector(bool sort, double scale) const {
	std::vector<double> offset_v = {};

	// We use a high level comparison check to avoid checking every loop if scale == 1.0
	if (scale == 1.0) {
		for (const SPtrTimedObject & to : to_v_) { offset_v.push_back(to->getOffsetMSec()); }
	}
	else {
		for (const SPtrTimedObject & to : to_v_) { offset_v.push_back(to->getOffsetMSec() / scale); }
	}
	
	if (sort) { std::sort(offset_v.begin(), offset_v.end()); } 

	return offset_v;
}
