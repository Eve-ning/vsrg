#include "stdafx.h"
#include "TimingPoint.h"


TimingPoint::TimingPoint(double offset_m_sec, double bpm, double time_sig_numerator, double time_sig_denominator) :
	EventObject(offset_m_sec), bpm_(bpm), time_sig_numerator_(time_sig_numerator), time_sig_denominator_(time_sig_denominator) {}

TimingPoint::~TimingPoint()
{
}

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

double TimingPoint::getBeatDurationMSec(double scale) {
	// Convert it to Minutes per Beat, then change Minutes to MSec
	return (scale * TimedObject::min_to_m_sec) / getBpm();
}

double TimingPoint::getMeasureDurationMSec(double scale) {
	return getBeatDurationMSec(getTimeSigNumerator()) * scale;
}

bool TimingPoint::isTimeSigValid() const {
	// Do we need negative Time Signatures? Will consider no until further discussion
	return (getTimeSigNumerator() > 0 && getTimeSigDenominator() > 0);
}

bool TimingPoint::isValid() const {
	return (TimedObject::isValid() && isTimeSigValid()) && (getBpm() > 0);
}

/// Gets info of the important object members

std::string TimingPoint::getInfo() const {
	return EventObject::getInfo() +
		"BPM " + std::to_string(bpm_) + '\n' +
		"Time Signature Numerator " + std::to_string(time_sig_numerator_) + '\n' +
		"Time Signature Denominator " + std::to_string(time_sig_denominator_) + '\n';
}
