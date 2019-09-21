#pragma once
#include "BaseObjects/Singular/Event/TimingPoint.h"
#include "EventParamsOsu.h"

// Denom not available, may be implemented in the future?
// TimingPointOsu(double offset_m_sec, double bpm, double time_sig_numerator, double time_sig_denominator);

class TimingPointOsu :
	public TimingPoint
{
public:

	TimingPointOsu(double offset_m_sec, double bpm, double time_sig_numerator);
	TimingPointOsu(const std::string & str);
	~TimingPointOsu();

	EventParamsOsu params;

	YAML::Node asYaml() const override;
};

