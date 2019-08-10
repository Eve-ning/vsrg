#include "stdafx.h"
#include "LongNote.h"

LongNote::LongNote(SPtrHitObject start_ho, SPtrHitObject end_ho) :
	start_ho_(start_ho), end_ho_(end_ho) {}

LongNote::LongNote(const LongNote & ln) {
	// Dynamic Pointer cast to promote from TimedObject to HitObject
	start_ho_ = std::dynamic_pointer_cast<HitObject>(ln.getStartNote()->Clone());
	end_ho_ = std::dynamic_pointer_cast<HitObject>(ln.getEndNote()->Clone());
}

LongNote::~LongNote()
{ // Do not delete SPtr explicitly!
}

SPtrHitObject LongNote::getStartNote() const {
	return start_ho_;
}

SPtrHitObject LongNote::getEndNote() const {
	return end_ho_;
}

void LongNote::setStartNote(SPtrHitObject start_ho) {
	start_ho_ = start_ho;
}

void LongNote::setEndNote(SPtrHitObject end_ho) {
	end_ho_ = end_ho;
}

double LongNote::getLength() {
	return end_ho_->getOffsetMSec() - start_ho_->getOffsetMSec();
}

bool LongNote::isBetween(double offset_ms, bool include_ends) const {
	if (include_ends) {
		return (offset_ms >= start_ho_->getOffsetMSec()) &&
			(offset_ms <= end_ho_->getOffsetMSec());
	}
	else {
		return (offset_ms > start_ho_->getOffsetMSec()) &&
			(offset_ms < end_ho_->getOffsetMSec());
	}
}

bool LongNote::isValid() const {
	if (bool(start_ho_) && bool(end_ho_)) { // Both must be valid separately
		// Start must be earlier than End
		bool valid_offset = start_ho_->getOffsetMSec() < end_ho_->getOffsetMSec();
		// Both must be on the same column
		bool valid_column = start_ho_->getColumn() == end_ho_->getColumn();
		return (valid_offset && valid_column);
	}
	else {
		return false;
	}
}

LongNote::operator bool() const
{
	return isValid();
}

std::string LongNote::getInfo() const {
	return "Start \n" + start_ho_->getInfo() +
		"End \n" + end_ho_->getInfo();
}

LongNote::operator std::string() const
{
	return getInfo();
}

bool LongNote::operator==(const LongNote & ln) const
{
	// Equivalent of comparing the HitObjects of the lns
	return (getStartNote() == ln.getStartNote()) &&
		   (getEndNote() == ln.getEndNote());
}

LongNote & LongNote::operator=(const LongNote & ln)
{
	// Dynamic Pointer cast to promote from TimedObject to HitObject
	setStartNote(std::dynamic_pointer_cast<HitObject>(ln.getStartNote()->Clone()));
	setEndNote(std::dynamic_pointer_cast<HitObject>(ln.getEndNote()->Clone()));

	return *this;
}
