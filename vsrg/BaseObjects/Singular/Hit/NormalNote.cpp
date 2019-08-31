#include "stdafx.h"
#include "NormalNote.h"

NormalNote::NormalNote() : HitObject(0, 0) {}

NormalNote::NormalNote(const double & offset_m_sec,
					   const int & index) :
	HitObject(offset_m_sec, index) {}
NormalNote::~NormalNote() {}

std::shared_ptr<TimedObject> NormalNote::Clone() const {
	return std::make_shared<NormalNote>(*this);
}

bool NormalNote::operator==(const NormalNote & nn) const {
	return (getOffset() == nn.getOffset()) &&
			    (getIndex() == nn.getIndex());
}

bool NormalNote::isOverlapping(const NormalNote & nn) const {
	return operator==(nn);
}
