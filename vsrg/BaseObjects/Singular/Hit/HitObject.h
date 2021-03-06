#pragma once
#include "BaseObjects/Singular/TimedObject.h"

/**
 * @brief A basic "Hittable" Abtract class used for secondary classes
 */
class HitObject : public TimedObject
{
public:
	/**
	 * @brief Construct a new Hit Object
	 * 
	 * @param offset_m_sec Offset of the object
	 * @param index Index of the object
	 */
	HitObject();
	HitObject(const double & offset_m_sec, const int & index);
	~HitObject() = 0;

	int getIndex() const;
	void setIndex(const int & index);

	/// Checks if 2 objects are overlapping. An alias to operator==
	virtual bool isOverlapping(const std::shared_ptr<HitObject> & ho) const;

	/// Validates the object being realistic
	virtual bool isValid() const override;

private:
	int index_;
};

typedef std::shared_ptr<HitObject> SPtrHitObject;
