#include "stdafx.h"
#include "LongNote.h"
#include "Helpers/MiscHelper.h"

LongNote::LongNote() {}

LongNote::LongNote(double offset_m_sec, unsigned int index, double length) :
	HitObject(offset_m_sec, index), length_m_sec_(length) {}

LongNote::~LongNote() {}

// To extend this via aesthetics PR

double LongNote::getLength(double unit_scale) {
	return length_m_sec_ * unit_scale;
}
void LongNote::setLength(double length, double unit_scale) {
	length_m_sec_ = length / unit_scale;
}

double LongNote::getOffsetEnd(double unit_scale) const {
	return getOffset(unit_scale) + length_m_sec_ * unit_scale;
}
void LongNote::setOffsetEnd(double offset_end_m_sec, double unit_scale) {
	length_m_sec_ = (offset_end_m_sec / unit_scale) - getOffset(unit_scale);
}

bool LongNote::isBetween(double offset, bool include_ends, double unit_scale) const {
	double difference = offset - getOffset();
	
	if (include_ends) {
		return (difference >= 0) && (difference <= length_m_sec_);
	}
	else {
		return (difference > 0) && (difference < length_m_sec_);
	}
}

bool LongNote::isOverlapping(const LongNote & ln, bool include_ends) const {
	BOOST_ASSERT_MSG(isValid() && ln.isValid(), "Both LongNotes must be Valid");
	
	return isBetween(ln.getOffset(), include_ends) ||
		isBetween(ln.getOffset(), include_ends);
}

bool LongNote::isValid() const {
	return HitObject::isValid() && length_m_sec_ > 0;
}

bool LongNote::operator==(const LongNote & ln) const {
	return isOverlapping(ln);
}
