#include "stdafx.h"
#include "TimingGridBase.h"

TimingGridBase::TimingGridBase(const size_t measures, const size_t beats, const size_t snaps, const double offset_ms, const double bpm) :
	tgm_v_(measures, TimingGridMeasure(beats, snaps, bpm)), offset_ms_(offset_ms) {}

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
std::vector<double> TimingGridBase::getBpm1DVector() const {
	std::vector<double> bpm_v;
	auto bpm_v_it = bpm_v.begin();
	for (const auto& tgm : tgm_v_) {
		std::vector<double> bpm_v_part = tgm.getBpm1DVector();
		bpm_v_it = std::copy(bpm_v_part.begin(), bpm_v_part.end(), bpm_v_it);
	}
	return bpm_v;
}

double TimingGridBase::length() const {
	double sum = 0.0;
	for (const auto& tgm : tgm_v_) sum += tgm.length();
	return sum;
void TimingGridBase::setBpm1DVector(const std::vector<double>& bpm_v) {
	auto bpm_start = bpm_v.begin();
	auto bpm_end = bpm_v.begin();
	std::vector<double> buffer;
	for (auto& tgm : tgm_v_) {
		bpm_end = bpm_start + tgm.size();
		std::copy(bpm_start, bpm_end, buffer.begin());
		tgm.setBpm1DVector(buffer);
		bpm_start = bpm_end;
	}
}

std::vector<std::vector<double>> TimingGridBase::getBpm2DVector() const {
	std::vector<std::vector<double>> bpm_2v;
	for (const auto& tgm : tgm_v_) bpm_2v.push_back(tgm.getBpmVector());
	return bpm_2v;
}

void TimingGridBase::setBpm2DVector(const std::vector<std::vector<double>>& bpm_2v) {
	BOOST_ASSERT_MSG(bpm_2v.size() == size(), "Incorrect Size");
	for (size_t i = 0; i < size(); i++) tgm_v_[i].setBpmVector(bpm_2v[i]);
}

// Getting offset is slow when it's large
// Will see which functions need a much faster access

double TimingGridBase::getOffsetAt(const size_t measure_i, const size_t beat_i, const size_t snap_i) {
	double offset = offset_ms_;
	for (size_t i = 0; i < measure_i; i++) { 
		offset += tgm_v_[i].length(); 
	}
	for (size_t i = 0; i < beat_i; i++) {
		offset += tgm_v_[measure_i][i].length();
	}
	offset += tgm_v_[measure_i][beat_i].snapLength() * snap_i;
	return offset;
}
