#pragma once
#include "TimedObject.h"

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
	 * @param column Column of the object
	 * @param starts_from Specify from what index the column starts from
	 */
	HitObject(const double & offset_m_sec, const int & column, const int & starts_from = 0);
	~HitObject(); // TODO: Make this virtual and move tests to separate categories

	/// Gets the column, specify starts_from to offset it to the correct index
	int getColumn(const int & starts_from = 0) const;

	/// Sets the column, specify starts_from to offset it to the correct index
	void setColumn(const int & column, const int & starts_from = 0);

	/// Checks if 2 objects are overlapping. An alias to operator==
	virtual bool isOverlapping(const HitObject & ho) const;

	/// Validates the object being realistic
	virtual bool isValid() const override;

	/// Gets info of the important object members
	virtual std::string getInfo() const override;

	virtual bool operator==(const HitObject & ho) const;

private:
	int column_;
};

typedef std::shared_ptr<HitObject> SPtrHitObject;
