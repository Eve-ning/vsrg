#include "stdafx.h"
#include "TimingGridSnap.h"

TimingGridSnap::TimingGridSnap(const size_t columns) :
	ho_v_(std::vector<SPtrHitObject>(columns, nullptr)) {}
TimingGridSnap::~TimingGridSnap() {}

SPtrHitObject TimingGridSnap::operator[](size_t i){
	return ho_v_[i]; 
}

std::vector<SPtrHitObject>& TimingGridSnap::getHitObjectVector() { return ho_v_; }
void TimingGridSnap::setHitObjectVector(const std::vector<SPtrHitObject>& ho_v) { ho_v_ = ho_v; }

size_t TimingGridSnap::size() const { return ho_v_.size(); }
