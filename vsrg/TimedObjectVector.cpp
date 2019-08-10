#include "stdafx.h"
#include "TimedObjectVector.h"

TimedObjectVector::TimedObjectVector() {
	ho_v_ = std::vector<SPtrTimedObject>();
}

TimedObjectVector::~TimedObjectVector() {}

TimedObjectVector::TimedObjectVector(TimedObjectVector & ho_v) {
	for (const SPtrTimedObject & ho : ho_v) {
		ho_v_.push_back(std::make_shared<TimedObject>(*ho));
	}
}

std::vector<SPtrTimedObject>::iterator TimedObjectVector::begin() { return ho_v_.begin(); }
std::vector<SPtrTimedObject>::iterator TimedObjectVector::end()   { return ho_v_.end();   }

SPtrTimedObject TimedObjectVector::getTimedObject(unsigned int index) const {
	return ho_v_.at(index);
}

SPtrTimedObject TimedObjectVector::operator[](unsigned int index) const {
	return getTimedObject(index);
}

TimedObjectVector TimedObjectVector::operator=(TimedObjectVector ho_v)
{
	ho_v_.clear();
	for (const SPtrTimedObject & ho : ho_v) {
		ho_v_.push_back(std::make_shared<TimedObject>(*ho));
	}
	return *this;
}

void TimedObjectVector::push_back(SPtrTimedObject ho) {
	ho_v_.push_back(ho);
}

void TimedObjectVector::pop_back() {
	ho_v_.pop_back();
}

void TimedObjectVector::clear() {
	ho_v_.clear();
}

size_t TimedObjectVector::size() const {
	return ho_v_.size();
}

std::vector<SPtrTimedObject> TimedObjectVector::getTimedObjectVector() const {
	return ho_v_;
}

void TimedObjectVector::setTimedObjectVector(const std::vector<SPtrTimedObject>& ho_v) {
	ho_v_ = ho_v;
}
