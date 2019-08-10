#include "stdafx.h"
#include "HitObjectVector.h"

HitObjectVector::HitObjectVector() {
	ho_v_ = std::vector<SPtrHitObject>();
}

HitObjectVector::~HitObjectVector() {}

HitObjectVector::HitObjectVector(HitObjectVector & ho_v) {
	for (const SPtrHitObject & ho : ho_v) {
		ho_v_.push_back(std::make_shared<HitObject>(*ho));
	}
}

std::vector<SPtrHitObject>::iterator HitObjectVector::begin() { return ho_v_.begin(); }
std::vector<SPtrHitObject>::iterator HitObjectVector::end()   { return ho_v_.end();   }

SPtrHitObject HitObjectVector::getHitObject(unsigned int index) const {
	return ho_v_.at(index);
}

SPtrHitObject HitObjectVector::operator[](unsigned int index) const {
	return getHitObject(index);
}

HitObjectVector HitObjectVector::operator=(HitObjectVector ho_v)
{
	ho_v_.clear();
	for (const SPtrHitObject & ho : ho_v) {
		ho_v_.push_back(std::make_shared<HitObject>(*ho));
	}
	return *this;
}

void HitObjectVector::push_back(SPtrHitObject ho) {
	ho_v_.push_back(ho);
}

void HitObjectVector::pop_back() {
	ho_v_.pop_back();
}

void HitObjectVector::clear() {
	ho_v_.clear();
}

size_t HitObjectVector::size() const {
	return ho_v_.size();
}

std::vector<SPtrHitObject> HitObjectVector::getHitObjectVector() const {
	return ho_v_;
}

void HitObjectVector::setHitObjectVector(const std::vector<SPtrHitObject>& ho_v) {
	ho_v_ = ho_v;
}
