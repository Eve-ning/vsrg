#pragma once
#include "HitObject.h"

/**
 * @brief NormalNote doesn't have any special implementation for now, it just extends from HitObject
 * We won't use HitObject as an actual Normal Note so as to allow flexibility in the future
 */
class NormalNote : public HitObject
{
public:
	/**
	 * @brief Construct a new Normal Note object
	 * 
	 * @param offset_m_sec Offset of the object
	 * @param column Column of the object
	 * @param starts_from Specify from what index the column starts from
	 */
	NormalNote(const double & offset_m_sec, const int & column, const int & starts_from = 0);
	~NormalNote();
	std::shared_ptr<TimedObject> Clone() const override;
	
	bool operator==(const NormalNote & nn) const;
	bool isOverlapping(const NormalNote & nn) const;
};

