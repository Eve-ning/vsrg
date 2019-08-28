#pragma once
#include <vector>
#include <algorithm>
#include "../../TimedObjects/TimedObject.h"

/**
 * @brief A class that wraps multiple TimedObjects for unique operations
 * 
 * Note that this can be treated largely as a std::vector, with similar functions
 * Iterators included
 */
class TimedObjectVector
{
public:
	virtual ~TimedObjectVector() = 0;

	std::vector<SPtrTimedObject>::iterator begin();
	std::vector<SPtrTimedObject>::iterator end();
	std::vector<SPtrTimedObject>::const_iterator cbegin() const;
	std::vector<SPtrTimedObject>::const_iterator cend() const;

	// Vector ops
	/// Alias to operator[]
	SPtrTimedObject getTimedObject(unsigned int index) const;
	SPtrTimedObject operator[](unsigned int index) const;
	void push_back(SPtrTimedObject to);
	void pop_back();
	void clear();
	bool isEmpty();
	size_t size() const;

	std::vector<double> getOffsetVector(bool sort = false,
		double unit_scale = TimedObject::UnitScale::msecond) const;
	
	/// Runs a cast check on the vector and returns a vector of matches of class specified
	template<class T>
	std::shared_ptr<std::vector<T>> getClassOnly() const {
		std::vector<T> filtered = {};
		std::for_each(cbegin(), cend(), [&filtered](const SPtrTimedObject & to) -> void {
			std::shared_ptr<T> casted = std::dynamic_pointer_cast<T>(to->Clone());
			if (casted) { filtered.push_back(*casted); }
		});

		return std::make_shared<std::vector<T>>(filtered);;
	}
	
	std::vector<SPtrTimedObject> getTimedObjectVector() const;	
	void setTimedObjectVector(const std::vector<SPtrTimedObject> & to_v);

	// While we could convert to Sec/Min/Hour, I think I'll leave it to them to convert via TimedObject
	double getEarliestOffset(double unit_scale = TimedObject::UnitScale::msecond) const;
	double getLatestOffset(double unit_scale = TimedObject::UnitScale::msecond) const;
	SPtrTimedObject getEarliestObject() const;
	SPtrTimedObject getLatestObject() const;

	/// Loops the vector and calls isValid for every element, returns the AND result
	bool isValid() const;
	/// Loops the vector and returns the indexes of invalid objects
	std::vector<unsigned int> isInvalidIndexes() const;
	/// Loops the vector and returns the invalid objects
	std::vector<SPtrTimedObject> isInvalidObjects() const;

	/// Loops the vector and calls toExport to push in vector
	virtual std::vector<std::string> toExport() const final;

	void multiplyOffsetMSec(double offset_m_sec);
	void divideOffsetMSec(double offset_m_sec);
	void addOffsetMSec(double offset_m_sec);
	void subtractOffsetMSec(double offset_m_sec);

	void operator*=(double offset_m_sec);
	void operator/=(double offset_m_sec);
	void operator+=(double offset_m_sec);
	void operator-=(double offset_m_sec);

private:

	std::vector<SPtrTimedObject> to_v_;
};
