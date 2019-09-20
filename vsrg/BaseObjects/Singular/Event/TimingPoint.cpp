#include "stdafx.h"
#include "TimingPoint.h"
#include "Helpers/MiscHelper.h"

/**
* @brief Construct a new Timing Point object
*
* See isValid() for validation checks on parameters
*
* @param offset_m_sec Offset in milliseconds
* @param bpm Beats per minute
* @param time_sig_numerator Time Signature Numerator, can be fractional
* @param time_sig_denominator Time Signature Denominator, can be fractional
*/

TimingPoint::TimingPoint() : bpm_(120.0), time_sig_numerator_(4), time_sig_denominator_(4) {}
TimingPoint::TimingPoint(
	double offset_m_sec,
	double bpm,
	double time_sig_numerator,
	double time_sig_denominator
) : EventObject(offset_m_sec),
	bpm_(bpm),
	time_sig_numerator_(time_sig_numerator),
	time_sig_denominator_(time_sig_denominator) {}
TimingPoint::TimingPoint(const YAML::Node & node) {
	fromYaml(node);
}
TimingPoint::~TimingPoint() {}

std::shared_ptr<TimedObject> TimingPoint::Clone() const {
	return std::make_shared<TimingPoint>(*this);
}

double TimingPoint::getBpm() const {
	return bpm_;
}
double TimingPoint::getTimeSigNumerator() const {
	return time_sig_numerator_;
}
double TimingPoint::getTimeSigDenominator() const {
	return time_sig_denominator_;
}
void TimingPoint::setBpm(double bpm) {	
	bpm_ = bpm;
}
void TimingPoint::setTimeSigNumerator(double time_sig_numerator) {
	time_sig_numerator_ = time_sig_numerator;
}
void TimingPoint::setTimeSigDenominator(double time_sig_denominator) {
	time_sig_denominator_ = time_sig_denominator;
}

double TimingPoint::getBeatDuration(double scale, double unit_scale) {
	// Convert it to Minutes per Beat, then change Minutes to MSec
	double beat_m_sec = (scale * TimedObject::UnitScale::minute) / getBpm();
	return beat_m_sec / unit_scale;
}
double TimingPoint::getMeasureDuration(double scale, double unit_scale) {
	double measure_m_sec = getBeatDuration(getTimeSigNumerator()) * scale;
	return measure_m_sec / unit_scale;
}

bool TimingPoint::isTimeSigValid() const {
	// Do we need negative Time Signatures? Will consider no until further discussion
	return (getTimeSigNumerator() > 0) &&
		   (getTimeSigDenominator() > 0);
}
bool TimingPoint::isValid() const {
	return TimedObject::isValid() && isTimeSigValid() && (getBpm() > 0);
}

YAML::Node TimingPoint::toYaml() const {
	auto out = EventObject::toYaml();
	out["bpm"] = StringHelper::formatDbl(bpm_);
	out["time_sig_numerator"] = time_sig_numerator_;
	out["time_sig_denominator"] = time_sig_denominator_;
	return out;
}

void TimingPoint::fromYaml(const YAML::Node & node) {
	EventObject::fromYaml(node);
	bpm_ = node["bpm"].as<double>();
	time_sig_numerator_ = node["time_sig_numerator"].as<double>();
	time_sig_denominator_ = node["time_sig_denominator"].as<double>();
}
