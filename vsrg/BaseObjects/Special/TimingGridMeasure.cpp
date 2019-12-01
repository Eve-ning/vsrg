#include "stdafx.h"
#include "TimingGridMeasure.h"

TimingGridMeasure::TimingGridMeasure(const size_t beats, const size_t snaps, const size_t columns) :
	tgb_v_(beats, TimingGridBeat(snaps, columns)) {}

TimingGridMeasure::~TimingGridMeasure() {}

TimingGridBeat& TimingGridMeasure::operator[](size_t i){
	return tgb_v_[i];
}

size_t TimingGridMeasure::size() const { return tgb_v_.size(); }

std::vector<double>& TimingGridMeasure::getBpmVector() const {
	std::vector<double> bpm_v = {};
	for (const auto& tgb : tgb_v_) bpm_v.push_back(tgb.getBpm());
	return bpm_v;
}

double TimingGridMeasure::length(double unit_scale) const {
	double sum = 0.0;
	for (const auto& tgb : tgb_v_) sum += tgb.length(unit_scale);
	return sum;
}
