#pragma once
#include <vector>
#include <algorithm>
#include "TimedObject.h"
#include "ScrollPoint.h" // TEMP CODE FOR INTELLISENSE

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

	std::vector<double> getOffsetHourVector(bool sort = false) const;
	std::vector<double> getOffsetMinVector(bool sort = false) const;
	std::vector<double> getOffsetSecVector(bool sort = false) const;
	std::vector<double> getOffsetMSecVector(bool sort = false) const;
	
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

	void multiplyOffsetMSec(double offset_m_sec);
	void divideOffsetMSec(double offset_m_sec);
	void addOffsetMSec(double offset_m_sec);
	void subtractOffsetMSec(double offset_m_sec);

	void operator*=(double offset_m_sec);
	void operator/=(double offset_m_sec);
	void operator+=(double offset_m_sec);
	void operator-=(double offset_m_sec);

private:

	/// Helper function for getOffset___Vector Variants. Scale scales the offset
	std::vector<double> getOffsetXVector(bool sort = false, double scale = 1.0) const;
	std::vector<SPtrTimedObject> to_v_;
};
