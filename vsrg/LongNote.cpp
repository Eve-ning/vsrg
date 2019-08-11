#include "stdafx.h"
#include "LongNote.h"

LongNote::LongNote(SPtrHitObject start_ho, SPtrHitObject end_ho) :
	start_ho_(start_ho), end_ho_(end_ho) {}
LongNote::LongNote(const LongNote & ln) {
	// Static Pointer cast to promote from TimedObject to HitObject
	start_ho_ = std::static_pointer_cast<HitObject>(start_ho_->Clone());
	end_ho_ = std::static_pointer_cast<HitObject>(end_ho_->Clone());
}
LongNote::~LongNote() {} // Do not delete SPtr explicitly!

LongNote LongNote::Clone() const {
	SPtrHitObject start_ho =
		std::static_pointer_cast<HitObject>(start_ho_->Clone());
	SPtrHitObject end_ho =
		std::static_pointer_cast<HitObject>(end_ho_->Clone());

	return LongNote(start_ho, end_ho);
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

bool LongNote::isBetween(double offset_m_sec, bool include_ends) const {
	if (include_ends) {
		return (offset_m_sec >= start_ho_->getOffsetMSec()) &&
			   (offset_m_sec <= end_ho_->getOffsetMSec());
	}
	else {
		return (offset_m_sec > start_ho_->getOffsetMSec()) &&
			   (offset_m_sec < end_ho_->getOffsetMSec());
	}
}

bool LongNote::isOverlapping(const LongNote & ln) {
	BOOST_ASSERT_MSG(isValid() && ln.isValid(), "Both LongNotes must be Valid");

	SPtrHitObject start_ho = getStartNote();
	SPtrHitObject start_ho_other = ln.getStartNote();

	// Indexes don't match, it cannot overlap
	if (start_ho->getIndex() !=
		start_ho_other->getIndex()) return false;

	SPtrHitObject end_ho_other = ln.getEndNote();

	// If either ends are in between, it overlaps
	if (isBetween(start_ho_other->getOffsetMSec()) ||
		  isBetween(end_ho_other->getOffsetMSec())) return true;
	
	return false;
}

bool LongNote::isValid() const {
	if (bool(start_ho_) && bool(end_ho_)) { // Both must be valid separately
		// Start must be earlier than End
		bool valid_offset =
			start_ho_->getOffsetMSec() < end_ho_->getOffsetMSec();
		// Both must be on the same index
		bool valid_index =
			start_ho_->getIndex() == end_ho_->getIndex();

		return (valid_offset && valid_index);
	}
	else {
		return false;
	}
}

LongNote::operator bool() const {
	return isValid();
}

std::string LongNote::getInfo() const {
	return
		"Start \n" + start_ho_->getInfo() +
		"End \n" + end_ho_->getInfo();
}

LongNote::operator std::string() const {
	return toExport();
}

bool LongNote::operator==(const LongNote & ln) const {
	// Equivalent of comparing the HitObjects of the lns
	return (getStartNote()->isOverlapping(ln.getStartNote())) &&
		     (getEndNote()->isOverlapping(ln.getEndNote()));
}

LongNote & LongNote::operator=(const LongNote & ln) {
	// Static Pointer cast to promote from TimedObject to HitObject
	setStartNote(std::static_pointer_cast<HitObject>(ln.getStartNote()->Clone()));
	setEndNote(  std::static_pointer_cast<HitObject>(ln.getEndNote()->Clone()));

	return *this;
}

std::string LongNote::toExport() const {
	BOOST_ASSERT_MSG(isValid(), "Both LongNotes must be Valid");
	return getInfo();
}
