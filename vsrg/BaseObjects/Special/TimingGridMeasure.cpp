#include "stdafx.h"
#include "TimingGridMeasure.h"

TimingGridMeasure::TimingGridMeasure(size_t beats, size_t snaps, double bpm) :
	tgb_v_(beats, TimingGridBeat(snaps, bpm)) {}

TimingGridMeasure::~TimingGridMeasure() {}

TimingGridBeat& TimingGridMeasure::operator[](size_t i){
	return tgb_v_[i];
}
TimingGridBeat TimingGridMeasure::operator[](size_t i) const {
	return tgb_v_[i];
}

bool TimingGridMeasure::isEmpty() const {
	for (const auto& tgb : tgb_v_) {
		if (!tgb.isEmpty()) return false;
	}
	return true;
}

size_t TimingGridMeasure::size() const { return tgb_v_.size(); }

std::vector<double> TimingGridMeasure::getBpm1DVector() const {
	std::vector<double> bpm_v = {};
	for (const auto& tgb : tgb_v_) bpm_v.push_back(tgb.getBpm());
	return bpm_v;
}

void TimingGridMeasure::setBpm1DVector(const std::vector<double>& bpm_v) {
	BOOST_ASSERT_MSG(bpm_v.size() == size(), "Incorrect Size");
	for (size_t i = 0; i < size(); i++) tgb_v_[i].setBpm(bpm_v[i]);
}

std::vector<TimingGridBeat> TimingGridMeasure::getTimingGridBeatVector() const { return tgb_v_; }
void TimingGridMeasure::setTimingGridBeatVector(const std::vector<TimingGridBeat>& tgb_v) { tgb_v_ = tgb_v; }

double TimingGridMeasure::length(double unit_scale) const {
	double sum = 0.0;
	for (const auto& tgb : tgb_v_) sum += tgb.length(unit_scale);
	return sum;
}

void TimingGridMeasure::simplify(size_t by) {
	auto save = tgb_v_; // Branch

	bool simplified = false;
	while (!simplified) {
		for (auto it = save.begin(); it != save.end(); it++) {
			if (!it->divide(by)) { // Divide until it runs into error
				simplified = true;
				break;
			}
		}
		if (!simplified) tgb_v_ = save;
	}
}
