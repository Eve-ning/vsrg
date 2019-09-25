#pragma once
#include "EventObject.h"

/**
 * @brief Inherits from EventObject, mainly used to time a song
 * 
 * While can be used to add effects, it's encouraged to not use this as it has triggerable validation functions that will trigger false positives unless turned off.
 * Recommend to use ScrollPoint instead for effects.
 * Measure Lines are not included in this, it needs to be inherited, then implemented. This is so that it's fully customizable and not hardcoded.
 */
class TimingPoint : public EventObject
{
public:
	/**
	 * @brief Construct a new Timing Point object
	 * 
	 * See isValid() for validation checks on parameters
	 * 
	 * @param offset_m_sec Offset in milliseconds
	 * @param bpm Beats per minute
	 * @param time_sig_numerator Time Signature Numerator, can be fractional
	 * @param time_sig_denominator Time Signature Denominator, can be fractional
	 */
	TimingPoint();
	TimingPoint(double offset_m_sec, double bpm, double time_sig_numerator, double time_sig_denominator);
	TimingPoint(const YAML::Node & node);
	~TimingPoint();

	std::string getYamlTag() const override;

	double getBpm() const;
	double getTimeSigNumerator() const;
	double getTimeSigDenominator() const;

	void setBpm(double bpm);
	void setTimeSigNumerator(double time_sig_numerator);
	void setTimeSigDenominator(double time_sig_denominator);

	/// Get the Beat Duration in Milliseconds scale defines the multiplier on the return value. 
	double getBeatDuration(double scale = 1.0,
		double unit_scale = TimedObject::UnitScale::msecond);
	/// Get the Measure Duration in Milliseconds scale defines the multiplier on the return value. 
	double getMeasureDuration(double scale = 1.0,
		double unit_scale = TimedObject::UnitScale::msecond);

	/// Checks if Time Signature is a valid fraction or if it equates to 0
	virtual bool isTimeSigValid() const;

	/// Validates the object being realistic
	virtual bool isValid() const override;

	virtual YAML::Node asYaml() const override;
	virtual void fromYaml(const YAML::Node & node) override;

private:
	/// Beats per Minute
	double bpm_;
	/// Time Signature Numerator
	double time_sig_numerator_;
	/// Time Signature Denominator
	double time_sig_denominator_;
};

typedef std::shared_ptr<TimingPoint> SPtrTimingPoint;