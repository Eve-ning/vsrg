#include "stdafx.h"
#include "TimingGridSnap.h"

TimingGridSnap::TimingGridSnap() : ho_v_() {}
TimingGridSnap::~TimingGridSnap() {}

SPtrHitObject& TimingGridSnap::operator[](size_t i){
	return ho_v_[i]; 
}

std::vector<SPtrHitObject> TimingGridSnap::getHitObjectVector() const { return ho_v_; }
void TimingGridSnap::setHitObjectVector(const std::vector<SPtrHitObject>& ho_v) { ho_v_ = ho_v; }

void TimingGridSnap::push_back(SPtrHitObject ho) {
	ho_v_.push_back(ho);
}

bool TimingGridSnap::isEmpty() const {
	for (const auto& ho : ho_v_) {
		if (ho != nullptr) return false;
	}
	return true;
}

size_t TimingGridSnap::size() const { return ho_v_.size(); }
