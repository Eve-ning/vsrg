#include "stdafx.h"
#include "LongNote.h"

LongNote::LongNote(double offset_m_sec, unsigned int index, double length) :
	HitObject(offset_m_sec, index), length_m_sec_(length) {}

LongNote::~LongNote() {} 

SPtrTimedObject LongNote::Clone() const {
	return std::make_shared<LongNote>(*this);
}

// To extend this via aesthetics PR

inline double LongNote::getLengthMSec() {
	return length_m_sec_;
}

inline void LongNote::setLengthMSec(double length_m_sec) {
	length_m_sec_ = length_m_sec;
}

double LongNote::getOffsetEndMSec() const {
	return getOffsetMSec() + length_m_sec_;
}
double LongNote::getOffsetEndSec() const {
	return getOffsetSec() + length_m_sec_ * TimedObject::sec_to_m_sec;
}
double LongNote::getOffsetEndMin() const {
	return getOffsetMin() + length_m_sec_ * TimedObject::min_to_m_sec;
}
double LongNote::getOffsetEndHour() const {
	return getOffsetHour() + length_m_sec_ * TimedObject::hour_to_m_sec;
}

inline void LongNote::setOffsetEndMSec(double offset_end_m_sec) {
	length_m_sec_ = (offset_end_m_sec - getOffsetEndMSec());
}

inline void LongNote::setOffsetEndSec(double offset_end_sec) {
	length_m_sec_ = (offset_end_sec - getOffsetEndSec()) / TimedObject::sec_to_m_sec;
}

inline void LongNote::setOffsetEndMin(double offset_end_min) {
	length_m_sec_ = (offset_end_min - getOffsetEndMin()) / TimedObject::min_to_m_sec;
}

inline void LongNote::setOffsetEndHour(double offset_end_hour) {
	length_m_sec_ = (offset_end_hour - getOffsetEndHour()) / TimedObject::hour_to_m_sec;
}

bool LongNote::isBetween(double offset_m_sec, bool include_ends) const {
	double difference = offset_m_sec - getOffsetMSec();
	
	if (include_ends) {
		return (difference >= 0) && (difference <= length_m_sec_);
	}
	else {
		return (difference > 0) && (difference < length_m_sec_);
	}
}

bool LongNote::isOverlapping(const LongNote & ln, bool include_ends) const {
	BOOST_ASSERT_MSG(isValid() && ln.isValid(), "Both LongNotes must be Valid");
	
	return isBetween(ln.getOffsetMSec(), include_ends) ||
		isBetween(ln.getOffsetEndMSec(), include_ends);
}

bool LongNote::isValid() const {
	return HitObject::isValid() && length_m_sec_ > 0;
}

std::string LongNote::getInfo() const {
	return HitObject::getInfo() +
		"Length " + std::to_string(length_m_sec_);
}

bool LongNote::operator==(const LongNote & ln) const {
	return isOverlapping(ln);
}

std::string LongNote::toExport() const {
	BOOST_ASSERT_MSG(isValid(), "Both LongNotes must be Valid");
	return getInfo();
}
