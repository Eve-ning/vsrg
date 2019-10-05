#pragma once
#include "BaseObjects/Singular/Event/TimingPoint.h"
#include "BaseObjects/Multiple/EventObjectVector.h"

/*
	This class is to facilitate measure bpm to ms bpm conversion
	This is supposed to be a general 
*/
class TimingPointMeasure
{
public:
	TimingPointMeasure() {}
	void fromSM(const std::string& str) {

	}
	void toSM(const SPtrEventObjectVector & eo_v) {

	}

private:
	std::vector<TimingPoint> tp_v_;
};

