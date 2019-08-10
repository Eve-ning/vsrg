#pragma once
#include <vector>
#include "HitObject.h"

/**
 * @brief A class that wraps multiple HitObjects for unique operations
 * 
 * Note that this can be treated largely as a std::vector, with similar functions
 * Iterators included
 */
class HitObjectVector
{
public:
	/// Initializes a blank HOV
	HitObjectVector();
	~HitObjectVector();
	/// Objects must be coerced to std::shared_ptr of HitObject.
	HitObjectVector(HitObjectVector & ho_v);

	std::vector<SPtrHitObject>::iterator begin();
	std::vector<SPtrHitObject>::iterator end();
	
	HitObjectVector operator=(HitObjectVector ho_v);

	// Vector ops
	/// Alias to operator[]
	SPtrHitObject getHitObject(unsigned int index) const;
	SPtrHitObject operator[](unsigned int index) const;
	void push_back(SPtrHitObject ho);
	void pop_back();
	void clear();
	size_t size() const;
	
	std::vector<SPtrHitObject> getHitObjectVector() const;	
	void setHitObjectVector(const std::vector<SPtrHitObject> & ho_v);
	
private:
	std::vector<SPtrHitObject> ho_v_;
};

