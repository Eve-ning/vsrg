#include "stdafx.h"
#include "TimingGridBase.h"

TimingGridBase::TimingGridBase(size_t measures, size_t beats, size_t snaps, double offset_ms, double bpm) :
	tgm_v_(measures, TimingGridMeasure(beats, snaps, bpm)), offset_ms_(offset_ms) {}

TimingGridBase::~TimingGridBase() {}

TimingGridMeasure& TimingGridBase::operator[](size_t i){
	return tgm_v_[i];
}
TimingGridMeasure TimingGridBase::operator[](size_t i) const {
	return tgm_v_[i];
}

bool TimingGridBase::isEmpty() const {
	for (const auto& tgm : tgm_v_) {
		if (!tgm.isEmpty()) return false;
	}
	return true;
}

size_t TimingGridBase::size() const { return tgm_v_.size(); }



double TimingGridBase::length() const {
	double sum = 0.0;
	for (const auto& tgm : tgm_v_) sum += tgm.length();
	return sum;
}

std::vector<double> TimingGridBase::getBpm1DVector() const {
	std::vector<double> bpm_v;
	auto bpm_v_it = bpm_v.begin();
	for (const auto& tgm : tgm_v_) {
		std::vector<double> bpm_v_part = tgm.getBpm1DVector();
		bpm_v_it = std::copy(bpm_v_part.begin(), bpm_v_part.end(), bpm_v_it);
	}
	return bpm_v;
}

void TimingGridBase::setBpm1DVector(const std::vector<double>& bpm_v) {
	auto bpm_start = bpm_v.begin();
	auto bpm_end = bpm_v.end();
	std::vector<double> buffer;
	for (auto& tgm : tgm_v_) {
		bpm_end = bpm_start + tgm.size();
		std::copy(bpm_start, bpm_end, std::back_inserter(buffer));
		tgm.setBpm1DVector(buffer);
		buffer.clear();
		bpm_start = bpm_end;
	}
}

std::vector<std::vector<double>> TimingGridBase::getBpm2DVector() const {
	std::vector<std::vector<double>> bpm_2v;
	for (const auto& tgm : tgm_v_) bpm_2v.push_back(tgm.getBpm1DVector());
	return bpm_2v;
}

void TimingGridBase::setBpm2DVector(const std::vector<std::vector<double>>& bpm_2v) {
	BOOST_ASSERT_MSG(bpm_2v.size() == size(), "Incorrect Size");
	for (size_t i = 0; i < size(); i++) tgm_v_[i].setBpm1DVector(bpm_2v[i]);
}

std::vector<TimingGridMeasure> TimingGridBase::getTimingGridMeasureVector() const { return tgm_v_; }
void TimingGridBase::setTimingGridMeasureVector(const std::vector<TimingGridMeasure>& tgm_v) { tgm_v_ = tgm_v; }

void TimingGridBase::setOffset(double offset_ms, double unit_scale) {
	offset_ms_ = offset_ms * unit_scale;
}

double TimingGridBase::getOffset() const {
	return offset_ms_;
}

double TimingGridBase::getOffset(const TimingGridIndex& index) const {
	double offset = offset_ms_;
	for (size_t i = 0; i < index.measure; i++) offset += tgm_v_[i].length(); 
	for (size_t i = 0; i < index.beat; i++)    offset += tgm_v_[index.measure][i].length();
	offset += tgm_v_[index.measure][index.beat].snapLength() * index.snap;
	return offset;
}

double TimingGridBase::getOffset(size_t measure, size_t beat, size_t snap) const {
	return getOffset(TimingGridIndex(measure, beat, snap));
}

TimingGridIndex TimingGridBase::getIndex(double offset_ms, double unit_scale) const {
	offset_ms *= unit_scale;
	// This is an offset search algorithm
	double offset_i = 0.0;
	TimingGridIndex index = TimingGridIndex(0, 0, 0);

	// These are save states, usually the most optimized would be
	// with measures, then beats, then snaps 
	TimingGridIndex index_m, index_b, index_s;
	double offset_m, offset_b, offset_s;

	// By Measures
	auto measure_i = tgm_v_.begin();
	while (offset_i + measure_i->length() <= offset_ms) { // If adding a measure length exceeds
		offset_i += measure_i->length();
		measure_i++;
		index.measure++;
		if (measure_i == tgm_v_.end()) throw std::out_of_range("Invalid Offset.");
	}
	// Save measure on next state
	index_m = index;
	index_m.measure++;
	offset_m = offset_i + measure_i->length();

	// By Beats
	auto tgb_v = measure_i->getTimingGridBeatVector();
	auto beat_i = tgb_v.begin();
	while (offset_i + beat_i->length() <= offset_ms) { // If adding a beat length exceeds 
		offset_i += beat_i->length();
		beat_i++;
		index.beat++;
		if (beat_i == tgb_v.end()) throw std::out_of_range("Invalid Offset.");
	}
	// Save beat on next state
	index_b = index;
	index_b.beat++;
	offset_b = offset_i + beat_i->length();

	// By Snaps
	double snap_length = beat_i->snapLength();
	index.snap = (size_t)(std::round((offset_ms - offset_i) / snap_length));

	// Save snap
	index_s = index;
	offset_s = offset_i + beat_i->snapLength() * index.snap;

	// We compare all states to see which one works best.
	// If there's a tie, we take the most optimized one.
	double error_s = abs(offset_ms - offset_s);
	double error_b = abs(offset_ms - offset_b);
	double error_m = abs(offset_ms - offset_m);
	constexpr double epsilon = std::numeric_limits<double>::epsilon();

	if (error_m - error_b < epsilon && error_m - error_s < epsilon) { return index_m; }
	else if (error_b - error_s < epsilon) { return index_b;  }
	else { return index_s; }
}

TimingGridSnap& TimingGridBase::getSnap(const TimingGridIndex& index) const {
	return tgm_v_[index.measure][index.beat][index.snap];
}

TimingGridSnap& TimingGridBase::getSnap(double offset_ms, double unit_scale) const {
	return getSnap(getIndex(offset_ms * unit_scale));
}

void TimingGridBase::setSnap(const TimingGridIndex& index, const std::vector<SPtrHitObject>& ho_v) {
	getSnap(index).setHitObjectVector(ho_v);
}

void TimingGridBase::setSnap(double offset_ms, const std::vector<SPtrHitObject>& ho_v,
						     double unit_scale) {
	setSnap(getIndex(offset_ms * unit_scale), ho_v);
}

void TimingGridBase::pushSnap(const TimingGridIndex& index, const SPtrHitObject& ho) {
	getSnap(index).push_back(ho);
}

void TimingGridBase::pushSnap(double offset_ms, const SPtrHitObject& ho,
					          double unit_scale) {
	pushSnap(getIndex(offset_ms * unit_scale), ho);
}

void TimingGridBase::pushMeasure(const TimingGridMeasure& tgm) {
	tgm_v_.push_back(tgm);
}

