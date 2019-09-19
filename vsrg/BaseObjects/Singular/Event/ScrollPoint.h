#pragma once
#include "EventObject.h"

/**
 * @brief Defines the Scroll Speed Multiplier at a certain point.
 * 
 * Use this instead of TimingPoint to modify scroll speed as it has more focused validation functions.
 */
class ScrollPoint : public EventObject
{
public:
	/**
	 * @brief Construct a new Scroll Point object
	 * 
	 * @param offset_m_sec Offset in Milliseconds
	 * @param scroll_speed_mult Scroll Speed multiplier. 1.0 is the base multiplier
	 */
	ScrollPoint();
	ScrollPoint(double offset_m_sec, double scroll_speed_mult = 1.0);
	~ScrollPoint();
	virtual std::shared_ptr<TimedObject> Clone() const override;

	double getScrollSpeedMult() const;
	void setScrollSpeedMult(double scroll_speed_mult);
		
	/// Checks if multiplier is negative, include0 determines if 0 is included
	bool isNegative(bool include0 = false) const;

	/// Checks if multiplier is positive, include0 determines if 0 is included
	bool isPositive(bool include0 = false) const;
	
	/**
	 * @brief Checks if the scroll speed is of a value with an optional threshold
	 * 
	 * @param value Value to check
	 * @param threshold The extended range to check, this adds to each end of the range
	 * @param include_ends To include ends of the checked range
	 * @return true Value is approximately equal or in the range
	 * @return false Value is not approximately equal or not in the range
	 */
	bool isApproximately(double value, double threshold = 0.0, bool include_ends = false) const;

	virtual YAML::Node toYaml() const override;

	/// Comparison Operator compares scroll_speed_mult
	bool operator>(double value) const;
	/// Comparison Operator compares scroll_speed_mult
	bool operator<(double value) const;
	/// Comparison Operator compares scroll_speed_mult
	bool operator>=(double value) const;
	/// Comparison Operator compares scroll_speed_mult
	bool operator<=(double value) const;
	/// Arithmetic Operator multiplies scroll_speed_mult
	ScrollPoint operator*(double by) const;
	/// Arithmetic Operator divides scroll_speed_mult
	ScrollPoint operator/(double by) const;
	/// Arithmetic Operator adds scroll_speed_mult
	ScrollPoint operator+(double by) const;
	/// Arithmetic O-erator subtracts scroll_speed_mult
	ScrollPoint operator-(double by) const;
	/// Assignment Arithmetic Operator multiplies scroll_speed_mult
	void operator*=(double by);
	/// Assignment Arithmetic Operator divides scroll_speed_mult
	void operator/=(double by);
	/// Assignment Arithmetic Operator adds scroll_speed_mult
	void operator+=(double by);
	/// Assignment Arithmetic Operator subtracts scroll_speed_mult
	void operator-=(double by);

private:
	/// Scroll Speed Multiplier
	double scroll_mult_;
};

