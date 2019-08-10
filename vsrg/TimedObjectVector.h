#pragma once
#include <vector>
#include "TimedObject.h"

/**
 * @brief A class that wraps multiple TimedObjects for unique operations
 * 
 * Note that this can be treated largely as a std::vector, with similar functions
 * Iterators included
 */
class TimedObjectVector
{
public:
	/// Initializes a blank TOV
	TimedObjectVector();
	~TimedObjectVector();
	/// Objects must be coerced to std::shared_ptr of TimedObject.
	TimedObjectVector(TimedObjectVector & to_v);

	std::vector<SPtrTimedObject>::iterator begin();
	std::vector<SPtrTimedObject>::iterator end();
	
	TimedObjectVector operator=(TimedObjectVector to_v);

	// Vector ops
	/// Alias to operator[]
	SPtrTimedObject getTimedObject(unsigned int index) const;
	SPtrTimedObject operator[](unsigned int index) const;
	void push_back(SPtrTimedObject to);
	void pop_back();
	void clear();
	size_t size() const;
	
	std::vector<SPtrTimedObject> getTimedObjectVector() const;	
	void setTimedObjectVector(const std::vector<SPtrTimedObject> & to_v);
	
private:
	std::vector<SPtrTimedObject> to_v_;
};

