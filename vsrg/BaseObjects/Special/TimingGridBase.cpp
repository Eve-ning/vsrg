#include "stdafx.h"
#include "TimingGridBase.h"

TimingGridBase::TimingGridBase(const size_t measures, const size_t beats, const size_t snaps) :
	tgm_v_(measures, TimingGridMeasure(beats, snaps)), offset_ms_(0.0) {}

TimingGridBase::~TimingGridBase() {}

TimingGridMeasure& TimingGridBase::operator[](size_t i){
	return tgm_v_[i];
}

bool TimingGridBase::isEmpty() const {
	for (const auto& tgm : tgm_v_) {
		if (!tgm.isEmpty()) return false;
	}
	return true;
}

size_t TimingGridBase::size() const { return tgm_v_.size(); }

std::vector<double> TimingGridBase::getBpmVector() const {
	std::vector<double> bpm_v;
	auto bpm_v_it = bpm_v.begin();
	for (const auto& tgm : tgm_v_) {
		std::vector<double> bpm_v_part = tgm.getBpmVector();
		bpm_v_it = std::copy(bpm_v_part.begin(), bpm_v_part.end(), bpm_v_it);
	}
	return bpm_v;
}

double TimingGridBase::length() const {
	double sum = 0.0;
	for (const auto& tgm : tgm_v_) sum += tgm.length();
	return sum;
}

// Getting offset is slow when it's large
// Will see which functions need a much faster access

double TimingGridBase::getOffsetAt(const size_t measure_i, const size_t beat_i, const size_t snap_i) {
	double offset = offset_ms_;
	for (size_t i = 0; i < measure_i; i++) offset += tgm_v_[i].length();
	for (size_t i = 0; i < beat_i; i++)    offset += tgm_v_[measure_i][i].length();
	offset += tgm_v_[measure_i][beat_i].snapLength() * snap_i;
	return offset;
}
