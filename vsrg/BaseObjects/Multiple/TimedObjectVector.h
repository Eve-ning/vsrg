#pragma once
#include <vector>
#include <algorithm>
#include "BaseObjects/Singular/TimedObject.h"

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
	std::vector<T> getClassOnly() const {
		// Note: May be a problem in the future if we're copying the vector over
		// Returning by reference doesn't really work though (?)
		std::vector<T> filtered = {};
		std::for_each(cbegin(), cend(), [&filtered](const SPtrTimedObject & to) -> void {
			std::shared_ptr<T> casted = std::dynamic_pointer_cast<T>(to->Clone());
			if (casted) { filtered.push_back(*casted); }
		});

		return filtered;
	}
	
	std::vector<SPtrTimedObject> getTimedObjectVector() const;	
	void setTimedObjectVector(const std::vector<SPtrTimedObject> & to_v);

	double getEarliestOffset(double unit_scale = TimedObject::UnitScale::msecond) const;
	double getLatestOffset(double unit_scale = TimedObject::UnitScale::msecond) const;
	SPtrTimedObject getEarliestObject() const;
	SPtrTimedObject getLatestObject() const;

	/// Loops the vector and calls isValid for every element, returns the AND result
	virtual bool isValid() const final;
	/// Loops the vector and returns the indexes of invalid objects
	virtual std::vector<unsigned int> isInvalidIndexes() const final;
	/// Loops the vector and returns the invalid objects
	virtual std::vector<SPtrTimedObject> isInvalidObjects() const final;

	/// Loops the vector and calls toYaml to push in vector
	virtual YAML::Node toYaml() const final;

	void multiplyOffsetMSec(double offset_m_sec);
	void divideOffsetMSec(double offset_m_sec);
	void addOffsetMSec(double offset_m_sec);
	void subtractOffsetMSec(double offset_m_sec);

	void operator*=(double offset_m_sec);
	void operator/=(double offset_m_sec);
	void operator+=(double offset_m_sec);
	void operator-=(double offset_m_sec);

protected:

	std::vector<SPtrTimedObject> to_v_;
};
