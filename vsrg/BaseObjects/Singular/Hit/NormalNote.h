#pragma once
#include "HitObject.h"

/**
 * @brief NormalNote doesn't have any special implementation for now, it just extends from HitObject
 * We won't use HitObject as an actual Normal Note so as to allow flexibility in the future
 */
class NormalNote : public HitObject
{
public:
	/**
	 * @brief Construct a new Normal Note object
	 * 
	 * @param offset_m_sec Offset of the object
	 * @param index Index of the object
	 */
	NormalNote();
	NormalNote(const double & offset_m_sec, const int & index);
	NormalNote(const YAML::Node & node);
	~NormalNote();
	std::shared_ptr<TimedObject> Clone() const override;

	std::string getYamlTag() const override;
	
	bool operator==(const NormalNote & nn) const;
	bool isOverlapping(const NormalNote & nn) const;	
};

