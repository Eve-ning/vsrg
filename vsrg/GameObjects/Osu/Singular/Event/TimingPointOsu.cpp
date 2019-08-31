#include "stdafx.h"
#include "TimingPointOsu.h"



TimingPointOsu::TimingPointOsu(double offset_m_sec, double bpm, double time_sig_numerator) :
	TimingPoint(offset_m_sec, bpm, time_sig_numerator, 4.0) {}

TimingPointOsu::TimingPointOsu(const std::string & str) {
	std::vector<std::string> str_v;
	boost::split(str_v, str, boost::is_any_of(","));

	setOffset(std::stod(str_v[0]));
	setBpm(60000.0 / std::stod(str_v[1]));
	setTimeSigNumerator(std::stod(str_v[2]));
	params.sample_ = std::stoi(str_v[3]);
	params.sample_index_ = std::stoi(str_v[4]);
	params.volume_ = std::stoi(str_v[5]);
	params.is_kiai_ = (str_v[7] == "1");
}

TimingPointOsu::~TimingPointOsu()
{
}
