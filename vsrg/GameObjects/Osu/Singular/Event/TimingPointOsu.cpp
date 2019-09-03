#include "stdafx.h"
#include "TimingPointOsu.h"
#include "Helpers/MiscHelper.h"

TimingPointOsu::TimingPointOsu(double offset_m_sec, double bpm, double time_sig_numerator) :
	TimingPoint(offset_m_sec, bpm, time_sig_numerator, 4.0) {}

TimingPointOsu::TimingPointOsu(const std::string & str) {
	auto it = IterHelper::tokenize(str, ",").begin();

	/* 0 */       setOffset(std::stod(*it));
	/* 1 */ it++; setBpm(60000.0 / std::stod(*it));
	/* 2 */ it++; setTimeSigNumerator(std::stod(*it));
	/* 3 */ it++; params.sample_	   = std::stoi(*it);
	/* 4 */ it++; params.sample_index_ = std::stoi(*it);
	/* 5 */ it++; params.volume_	   = std::stoi(*it);
	/* 6 */ it++;
	/* 7 */ it++; params.is_kiai_	   = (*it == "1");
}
TimingPointOsu::~TimingPointOsu()
{
}
