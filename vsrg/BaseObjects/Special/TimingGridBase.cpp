#include "stdafx.h"
#include "TimingGridBase.h"


TimingGridBase::TimingGridBase(const size_t measures, const size_t beats, const size_t snaps, const size_t columns) :
	tgm_v_(measures, TimingGridMeasure(beats, snaps, columns)) {}

TimingGridBase::~TimingGridBase() {}

TimingGridMeasure& TimingGridBase::operator[](size_t i){
	return tgm_v_[i];
}

size_t TimingGridBase::size() const { return tgm_v_.size(); }

std::vector<double>& TimingGridBase::getBpmVector() const {
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
