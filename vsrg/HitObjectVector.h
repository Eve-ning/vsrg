#pragma once
#include <vector>
#include "HitObject.h"

class HitObjectVector
{
public:
	HitObjectVector(const std::vector<HitObject> & ho_v);
	HitObjectVector();
	~HitObjectVector();
	HitObjectVector(HitObjectVector & ho_v);

	std::vector<SPtrHitObject>::iterator begin();
	std::vector<SPtrHitObject>::iterator end();
	SPtrHitObject operator[](unsigned int index) const;
	HitObjectVector operator=(HitObjectVector ho_v);
	void push_back(SPtrHitObject ho);
	void pop_back();
	void clear();
	size_t size() const;
	
	/// Gets the whole HitObjectVector
	std::vector<SPtrHitObject> getHitObjectVector() const;	
	/// Sets the whole HitObjectVector
	void setHitObjectVector(const std::vector<SPtrHitObject> & ho_v);
	/// Gets the HitObject via index, alias to operator[]
	SPtrHitObject getHitObject(unsigned int index) const;


private:
	std::vector<SPtrHitObject> ho_v_;
};

