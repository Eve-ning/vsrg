#pragma once
#include "BaseObjects/Special/TimingGridBase.h"
#include "GameObjects/SM/Singular/Event/TimingPointSM.h"

class TimingGridBaseSM :
	public TimingGridBase
{
public:
	// If measures always contain the same amount of beats
	TimingGridBaseSM(size_t measures = 0,
				     size_t beats = 0,
				     size_t snaps = 0,
				     double offset_ms = 0.0,
		double bpm = 0.0);

	~TimingGridBaseSM();

	template<class TimingPointClass>
	void loadFromMS(const SPtrEventObjectVector& eo_v,
					const SPtrHitObjectVector& ho_v) {
		auto tp_v = eo_v->getClassOnly<TimingPointClass>();
		double ho_offset_last = ho_v->getLatestOffset();

		// Sorts the vector
		std::sort(tp_v.begin(), tp_v.end()); 
		setBpm(tp_v, ho_offset_last);
		setNotes(ho_v);
	}

private:

	template<class TimingPointClass>
	void setBpm(const std::vector<TimingPointClass> tp_v,
				double last_offset) {
		std::vector<double> bpm_1v; // We will grab the 1D Vec
		auto tp_i = tp_v.begin();
		double offset = tp_i->getOffset();
		double offset_next = (tp_i + 1 == tp_v.end()) ? DBL_MAX : (tp_i + 1)->getOffset();
		double offset_diff = 0.0;
		TimingGridMeasure tgm = TimingGridMeasure(0, 0, 0);
		while (offset < last_offset && tp_i != tp_v.end()) {
			tgm = TimingGridMeasure(4, 192, tp_i->getBpm());
			if (offset + tgm.length() > offset_next) {
				// Override BPM https://github.com/Eve-ning/vsrg/wiki/MS-to-SM-System-Conversion
				offset_diff = offset_next - offset;
				tgm = TimingGridMeasure(4, 192, (4000 / offset_diff));
				offset_next = (tp_i + 1 == tp_v.end()) ? DBL_MAX : (tp_i + 1)->getOffset();
			}
			pushMeasure(tgm);
			offset += tgm.length();
			if (abs(offset_next - offset) < DBL_EPSILON) tp_i++;
		}
	}

	void setNotes(const SPtrHitObjectVector& ho_v) {
		for (int i = 0; i < ho_v->size(); i ++) {
			pushSnap(ho_v->operator[](i)->getOffset(), ho_v->operator[](i));
		}
	}
	
};

