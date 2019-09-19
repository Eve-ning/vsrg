#pragma once
#include <string>
#include <map>
#include "yaml-cpp/yaml.h"

/**
 * @brief Abstract Class, used for all "timable" objects

 * Note that it stores the offset in ms,
 * so any function that requires it in other units will call a converter
 */
class TimedObject
{
public:
	TimedObject();
	TimedObject(double offset_m_sec);
	virtual ~TimedObject() = 0;

	virtual std::shared_ptr<TimedObject> Clone() const = 0;

	struct UnitScale {
		/// Value of ratio of Hour:Millisecond
		static const double hour;
		/// Value of ratio of Minute:Millisecond
		static const double minute;
		/// Value of ratio of Second:Millisecond
		static const double second;
		/// Value of ratio of Millisecond:Millisecond
		/// (added for clarity of function usage)
		static const double msecond;
	};

	/// Gets Offset in milliseconds
	double getOffset(double unit_scale = TimedObject::UnitScale::msecond) const;

	/// Sets Offset in milliseconds
	void setOffset(double offset_m_sec, double unit_scale = TimedObject::UnitScale::msecond);

	/// Validates the object being realistic
	virtual bool isValid() const;
	virtual operator bool() const final; // Calls isValid

	/// Gets info of the important object members
	virtual YAML::Node toYaml() const;
	virtual void fromYaml(const YAML::Node & node);

	virtual bool operator==(const TimedObject & obj) const;
	virtual bool operator>(const TimedObject & obj) const;
	virtual bool operator<(const TimedObject & obj) const;
	virtual bool operator<=(const TimedObject & obj) const;
	virtual bool operator>=(const TimedObject & obj) const;
	std::shared_ptr<TimedObject> operator*(double by_m_sec) const;
	std::shared_ptr<TimedObject> operator/(double by_m_sec) const;
	std::shared_ptr<TimedObject> operator+(double by_m_sec) const;
	std::shared_ptr<TimedObject> operator-(double by_m_sec) const;
	virtual void operator*=(double by_m_sec);
	virtual void operator/=(double by_m_sec);
	virtual void operator+=(double by_m_sec);
	virtual void operator-=(double by_m_sec);

private:
	/// Stored value in milliseconds
	double offset_m_sec_;
};

typedef std::shared_ptr<TimedObject> SPtrTimedObject;