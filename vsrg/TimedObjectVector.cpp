#include "stdafx.h"
#include "TimedObjectVector.h"

TimedObjectVector::TimedObjectVector() {
	to_v_ = std::vector<SPtrTimedObject>();
}

TimedObjectVector::~TimedObjectVector() {}

TimedObjectVector::TimedObjectVector(TimedObjectVector & to_v) {
	for (const SPtrTimedObject & to : to_v) {
		to_v_.push_back(std::make_shared<TimedObject>(*to));
	}
}

std::vector<SPtrTimedObject>::iterator TimedObjectVector::begin() { return to_v_.begin(); }
std::vector<SPtrTimedObject>::iterator TimedObjectVector::end()   { return to_v_.end();   }

SPtrTimedObject TimedObjectVector::getTimedObject(unsigned int index) const {
	return to_v_.at(index);
}

SPtrTimedObject TimedObjectVector::operator[](unsigned int index) const {
	return getTimedObject(index);
}

TimedObjectVector TimedObjectVector::operator=(TimedObjectVector to_v)
{
	to_v_.clear();
	for (const SPtrTimedObject & to : to_v) {
		to_v_.push_back(std::make_shared<TimedObject>(*to));
	}
	return *this;
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

size_t TimedObjectVector::size() const {
	return to_v_.size();
}

std::vector<SPtrTimedObject> TimedObjectVector::getTimedObjectVector() const {
	return to_v_;
}

void TimedObjectVector::setTimedObjectVector(const std::vector<SPtrTimedObject>& to_v) {
	to_v_ = to_v;
}
