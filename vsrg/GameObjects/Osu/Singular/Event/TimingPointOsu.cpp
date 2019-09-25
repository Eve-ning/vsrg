#include "stdafx.h"
#include "TimingPointOsu.h"
#include "Helpers/MiscHelper.h"

TimingPointOsu::TimingPointOsu(double offset_m_sec, double bpm, double time_sig_numerator) :
	TimingPoint(offset_m_sec, bpm, time_sig_numerator, 4.0), params(){}

TimingPointOsu::TimingPointOsu(const std::string & str) {
	auto tokens = IterHelper::tokenize(str, ",", 8U);
	auto it = tokens.cbegin();

	/* 0 */       setOffset(std::stod(*it));
	/* 1 */ it++; setBpm(60000.0 / std::stod(*it));
	/* 2 */ it++; setTimeSigNumerator(std::stod(*it));
	/* 3 */ it++; params.sample_	   = std::stoul(*it);
	/* 4 */ it++; params.sample_index_ = std::stoul(*it);
	/* 5 */ it++; params.volume_	   = std::stoul(*it);
	/* 6 */ it++;
	/* 7 */ it++; params.is_kiai_	   = (*it == "1");
}
TimingPointOsu::~TimingPointOsu()
{
}

SPtrTimedObject TimingPointOsu::Clone() const {
	return std::make_shared<TimingPointOsu>(*this);
}

std::string TimingPointOsu::asNative() const {
	std::string out = "";
	out += std::to_string(getOffset()) +
		',' + std::to_string(60000.0 / getBpm()) +
		',' + std::to_string((unsigned int) getTimeSigNumerator()) +
		',' + std::to_string(params.sample_) +
		',' + std::to_string(params.sample_index_) +
		',' + std::to_string(params.volume_) +
		',' + '1' +
		',' + (params.is_kiai_ ? '1' : '0');
	return std::move(out);
}