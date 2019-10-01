#include "stdafx.h"
#include "TimedObjectVector.h"

TimedObjectVector::~TimedObjectVector() {}

std::vector<SPtrTimedObject>::iterator TimedObjectVector::begin() {
	return to_v_.begin();
}
std::vector<SPtrTimedObject>::iterator TimedObjectVector::end() {
	return to_v_.end();  
}
std::vector<SPtrTimedObject>::const_iterator TimedObjectVector::cbegin() const {
	return to_v_.cbegin();
}
std::vector<SPtrTimedObject>::const_iterator TimedObjectVector::cend() const {
	return to_v_.cend();
}

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

std::vector<SPtrTimedObject> TimedObjectVector::getTimedObjectVector() const {
	return to_v_;
}
void TimedObjectVector::setTimedObjectVector(const std::vector<SPtrTimedObject>& to_v) {
	to_v_ = to_v;
}

double TimedObjectVector::getEarliestOffset(double unit_scale) const {
	std::vector<double> offset_v = getOffsetVector(false, unit_scale);
	return *std::min_element(offset_v.cbegin(), offset_v.cend());
}
double TimedObjectVector::getLatestOffset(double unit_scale) const {
	std::vector<double> offset_v = getOffsetVector(false, unit_scale);
	return *std::max_element(offset_v.cbegin(), offset_v.cend());
}

SPtrTimedObject TimedObjectVector::getEarliestObject() const {
	return *std::min_element(cbegin(), cend());
}
SPtrTimedObject TimedObjectVector::getLatestObject() const {
	return *std::max_element(cbegin(), cend());
}

SPtrTimedObject TimedObjectVector::getLowerObject(double offset, double unit_scale) const {
	return *std::lower_bound(cbegin(), cend(), (offset / unit_scale));
}

SPtrTimedObject TimedObjectVector::getUpperObject(double offset, double unit_scale) const {
	return *std::upper_bound(cbegin(), cend(), (offset / unit_scale));}

bool TimedObjectVector::isValid() const {
	// Using std::for_each raises a warning for some reason

	// Runs through the whole vector to find any isValid == false, return false if found
	for (const SPtrTimedObject & to : getTimedObjectVector()) {
		if (!to->isValid()) return false; 
	}

	return true;
}

std::vector<unsigned int> TimedObjectVector::isInvalidIndexes() const {
	std::vector<unsigned int> invalid_index_v = {};
	unsigned int index = 0;
	std::for_each(cbegin(), cend(),
		[&index, &invalid_index_v](const SPtrTimedObject & to) {
		if (!to->isValid()) { invalid_index_v.push_back(index); }
		index++;
	});
	return invalid_index_v;
}

std::vector<SPtrTimedObject> TimedObjectVector::isInvalidObjects() const {
	std::vector<SPtrTimedObject> invalid_obj_v = {};
	std::for_each(cbegin(), cend(),
		[&invalid_obj_v](SPtrTimedObject to) { // Note to copy the SPtr
		if (!to->isValid()) { invalid_obj_v.push_back(to); };
	});
	return invalid_obj_v;
}

void TimedObjectVector::multiplyOffsetMSec(double offset_m_sec) {
	std::transform(begin(), end(), begin(),
		[offset_m_sec](SPtrTimedObject & to) -> SPtrTimedObject {
		to->operator*=(offset_m_sec); return to;
	});
}

void TimedObjectVector::divideOffsetMSec(double offset_m_sec) {
	std::transform(begin(), end(), begin(),
		[offset_m_sec](SPtrTimedObject & to) -> SPtrTimedObject {
		to->operator/=(offset_m_sec); return to;
	});
}

void TimedObjectVector::addOffsetMSec(double offset_m_sec) {
	std::transform(begin(), end(), begin(),
		[offset_m_sec](SPtrTimedObject & to) -> SPtrTimedObject {
		to->operator+=(offset_m_sec); return to;
	});
}

void TimedObjectVector::subtractOffsetMSec(double offset_m_sec) {
	std::transform(begin(), end(), begin(),
		[offset_m_sec](SPtrTimedObject & to) -> SPtrTimedObject {
		to->operator-=(offset_m_sec); return to;
	});
}

void TimedObjectVector::operator*=(double offset_m_sec) {
	multiplyOffsetMSec(offset_m_sec);
}
void TimedObjectVector::operator/=(double offset_m_sec) {
	divideOffsetMSec(offset_m_sec);
}
void TimedObjectVector::operator+=(double offset_m_sec) {
	addOffsetMSec(offset_m_sec);
}
void TimedObjectVector::operator-=(double offset_m_sec) {
	subtractOffsetMSec(offset_m_sec);
}

std::vector<double> TimedObjectVector::getOffsetVector(bool sort, double unit_scale) const {
	std::vector<double> offset_v = {};

	for (const SPtrTimedObject & to : to_v_) {
		offset_v.push_back(to->getOffset(unit_scale));
	}

	if (sort) { std::sort(offset_v.begin(), offset_v.end()); } 

	return offset_v;
}
