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
	/**
	 * @brief Checks if the object is between the 2 Hit Objects
	 * 
	 * @param offset_ms The offset to check if it's in between
	 * @param include_ends To include the end points in the range
	 * @return true Offset is in between the Long Note ends
	 * @return false Offset is not in between the Long Note ends
	 */
	virtual bool isBetween(double offset_ms, bool include_ends = false) const;

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

