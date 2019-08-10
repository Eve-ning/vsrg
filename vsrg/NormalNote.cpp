#include "stdafx.h"
#include "NormalNote.h"


NormalNote::NormalNote(const double & offset_m_sec,
					   const int & index,
					   const int & starts_from) :
	HitObject(offset_m_sec, index, starts_from)
{
}


NormalNote::~NormalNote()
{
}

std::shared_ptr<TimedObject> NormalNote::Clone() const {
	return std::make_shared<NormalNote>(*this);
}

bool NormalNote::operator==(const NormalNote & nn) const
{
	return (getOffsetMSec() == nn.getOffsetMSec()) &&
		(getIndex() == nn.getIndex());
}

bool NormalNote::isOverlapping(const NormalNote & nn) const {
	return operator==(nn);
}
