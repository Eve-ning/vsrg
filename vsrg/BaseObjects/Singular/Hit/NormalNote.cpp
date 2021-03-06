#include "stdafx.h"
#include "NormalNote.h"

NormalNote::NormalNote() {}

NormalNote::NormalNote(const double & offset_m_sec,
					   const int & index) :
	HitObject(offset_m_sec, index) {}
NormalNote::~NormalNote() {}

bool NormalNote::operator==(const NormalNote & nn) const {
	return (getOffset() == nn.getOffset()) &&
			    (getIndex() == nn.getIndex());
}

bool NormalNote::isOverlapping(const NormalNote & nn) const {
	return operator==(nn);
}
