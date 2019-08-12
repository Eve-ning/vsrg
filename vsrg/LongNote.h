#pragma once
#include "HitObject.h"
#include <vector>
// Creates a Long/Held Note with 2 Hit Objects
class LongNote : public HitObject
{
public:
	/**
	 * @brief Construct a new Long Note object
	 * 
	 * @param start_ho The start Hit Object as a shared pointer
	 * @param end_ho The end Hit Object as a shared pointer
	 */
	LongNote(double offset_m_sec, unsigned int index, double length);
	~LongNote();
	/// Deep Copies the 2 HitObjects into a new LongNote
	SPtrTimedObject Clone() const;

	// To extend this via aesthetics PR
	virtual double getLengthMSec();
	virtual void setLengthMSec(double length_m_sec);

	virtual double getOffsetEndMSec() const;
	virtual double getOffsetEndSec() const;
	virtual double getOffsetEndMin() const;
	virtual double getOffsetEndHour() const;
	
	virtual void setOffsetEndMSec(double offset_end_m_sec);
	virtual void setOffsetEndSec(double offset_end_sec);
	virtual void setOffsetEndMin(double offset_end_min);
	virtual void setOffsetEndHour(double offset_end_hour);

    /// If the offset is between the 2 Hit Objects include_ends to include the end points in the range
	virtual bool isBetween(double offset_m_sec, bool include_ends = false) const;

	virtual bool isOverlapping(const LongNote & ln, bool include_ends = false) const;

	/// Validates the object being realistic
	virtual bool isValid() const;

	/// Gets info of the important object members
	virtual std::string getInfo() const;
	/// toExport handles the string exported to files, unlike getInfo which prints more details
	virtual std::string toExport() const;

	virtual bool operator==(const LongNote & ln) const;

private:
	double length_m_sec_;
};

