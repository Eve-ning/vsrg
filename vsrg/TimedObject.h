#pragma once
#include <string>

/**
 * @brief Abstract Class, used for all "timable" objects

 * Note that it stores the offset in ms,
 * so any function that requires it in other units will call a converter
 */
class TimedObject
{
public:
	TimedObject(double offset_m_sec);
	virtual ~TimedObject() = 0;

	virtual std::shared_ptr<TimedObject> Clone() const = 0;

	/// Gets Offset in milliseconds
	double getOffsetMSec() const; 
	/// Gets Offset in seconds
	double getOffsetSec() const;
	/// Gets Offset in minutes
	double getOffsetMin() const;
	/// Gets Offset in hours
	double getOffsetHour() const;

	/// Sets Offset in milliseconds
	void setOffsetMSec(const double & offset_m_sec);
	/// Sets Offset in seconds
	void setOffsetSec(const double & offset_sec);
	/// Sets Offset in minutes
	void setOffsetMin(const double & offset_min);
	/// Sets Offset in hours
	void setOffsetHour(const double & offset_hour);

	/// Validates the object being realistic
	virtual bool isValid() const;
	virtual operator bool() const final; // Calls isValid

	/// Gets info of the important object members
	virtual std::string getInfo() const;
	virtual std::string toExport() const;
	virtual operator std::string() const final; // Calls getInfo

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

	/// Value of ratio of Hour:Millisecond
	static const double hour_to_m_sec;
	/// Value of ratio of Minute:Millisecond
	static const double min_to_m_sec;
	/// Value of ratio of Second:Millisecond
	static const double sec_to_m_sec;

private:
	/// Stored value in milliseconds
	double offset_m_sec_;
};

typedef std::shared_ptr<TimedObject> SPtrTimedObject;