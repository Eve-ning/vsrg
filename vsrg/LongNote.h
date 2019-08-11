#pragma once
#include "HitObject.h"
#include <vector>
// Creates a Long/Held Note with 2 Hit Objects
class LongNote
{
public:
	/**
	 * @brief Construct a new Long Note object
	 * 
	 * @param start_ho The start Hit Object as a shared pointer
	 * @param end_ho The end Hit Object as a shared pointer
	 */
	LongNote(SPtrHitObject start_ho, SPtrHitObject end_ho);
	LongNote(const LongNote & ln);
	~LongNote();
	/// Deep Copies the 2 HitObjects into a new LongNote
	LongNote Clone() const;

	/// Gets a copied shared_ptr of the Start Hit Object
	SPtrHitObject getStartNote() const;
	/// Gets a copied shared_ptr of the End Hit Object
	SPtrHitObject getEndNote() const;

	/// Sets a copied shared_ptr of the Start HitObject
	void setStartNote(SPtrHitObject start_ho);
	/// Sets a copied shared_ptr of the End Hit Object
	void setEndNote(SPtrHitObject end_ho);

	/// Gets the distance between the two Hit Objects
	virtual double getLength();
    /// If the offset is between the 2 Hit Objects include_ends to include the end points in the range
	virtual bool isBetween(double offset_m_sec, bool include_ends = false) const;

	virtual bool isOverlapping(const LongNote & ln);

	/// Validates the object being realistic
	virtual bool isValid() const;
	virtual operator bool() const; // Calls isValid

	/// Gets info of the important object members
	virtual std::string getInfo() const;
	virtual operator std::string() const; // Calls getInfo

	virtual bool operator==(const LongNote & ln) const;
	LongNote &   operator= (const LongNote & ln);

private:
	SPtrHitObject start_ho_;
	SPtrHitObject end_ho_;
};

