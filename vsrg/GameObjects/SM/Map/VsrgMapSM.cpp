#include "stdafx.h"
#include "VsrgMapSM.h"
#include "GameObjects/SM/Singular/Event/TimingPointSM.h"
#include "GameObjects/SM/Singular/Event/StopPointSM.h"
#include "GameObjects/SM/Multiple/EventObjectVectorSM.h"
#include "GameObjects/SM/Multiple/HitObjectVectorSM.h"

VsrgMapSM::VsrgMapSM() : VsrgMap() {
	auto eo = EventObjectVectorSM();
	auto ho = HitObjectVectorSM();
	eo_v_ = std::make_shared<EventObjectVectorSM>(eo);
	ho_v_ = std::make_shared<HitObjectVectorSM>(ho);
}

VsrgMapSM::~VsrgMapSM() {}

void VsrgMapSM::loadFile(const std::string& file_path) {
	// Reference: https://github.com/stepmania/stepmania/wiki/sm

	std::vector<std::string> file_contents = readFile(file_path);

	std::vector<std::string>::const_iterator it = file_contents.cbegin();
	std::vector<std::string>::const_iterator ite = file_contents.cend();

	auto u_map = toUMap(it, ite);

	// Tries to get value, if not found then we return "" 1-populated vector
	auto getValue = [&](const std::string & str)->std::vector<std::string> {
		auto f = u_map.find(str);
		return f == u_map.end() ? std::vector<std::string>({ "" }) : f->second;
	};

	params.title_						=			getValue("#TITLE")[0];
	params.subtitle_					=			getValue("#SUBTITLE")[0];
	params.artist_						=			getValue("#ARTIST")[0];
	params.title_u_						=			getValue("#TITLETRANSLIT")[0];
	params.subtitle_u_					=			getValue("#SUBTITLETRANSLIT")[0];
	params.artist_u_					=			getValue("#ARTISTTRANSLIT")[0];
	params.genre_						=			getValue("#GENRE")[0];
	params.creator_						=			getValue("#CREDIT")[0];
	params.audio_path_					=			getValue("#MUSIC")[0];
	params.bn_path_						=			getValue("#BANNER")[0];
	params.bg_path_						=			getValue("#BACKGROUND")[0];
	//NULL								=			getValue("#LYRICSPATH")[0];
	params.cd_path_						=			getValue("#CDTITLE")[0];
	params.preview_time_start_			= std::stod(getValue("#SAMPLESTART")[0]);
	params.preview_time_end_			= std::stod(getValue("#SAMPLELENGTH")[0]) + params.preview_time_start_;
	//NULL								=			getValue("#SELECTABLE")[0];
	params.offset_						= std::stod(getValue("#OFFSET")[0]);
	std::vector<std::string> bpm_str	=			getValue("#BPMS");
	std::vector<std::string> stop_str	=			getValue("#STOPS");
	params.display_bpm_					=			getValue("#DISPLAYBPM")[0];
	//NULL								=			getValue("#BGCHANGES:")[0];
	//NULL								=			getValue("#FGCHANGES:")[0];

	std::vector<std::string> notes_str	=			getValue("#NOTES")	; // Move i	t to #NOTES	

	params.chart_type_		=	notes_str[2]; params.chart_type_		.pop_back();
	params.group_			=	notes_str[3]; params.group_				.pop_back();
	params.difficulty_name_ =	notes_str[4]; params.difficulty_name_	.pop_back();
	params.difficulty_val_	=	notes_str[5]; params.difficulty_val_	.pop_back();

	auto bpm_pairs = processBpms(bpm_str.begin(), bpm_str.end(), params.offset_);
	processStops(stop_str.begin(), stop_str.end());
	processHO(notes_str.begin() + 6, notes_str.end());

}

void VsrgMapSM::saveFile(const std::string& file_path, bool overwrite) {

}

std::vector<std::pair<double, double>>
VsrgMapSM::processBpms(const std::vector<std::string>::iterator& begin,
					   const std::vector<std::string>::iterator & end,
					   double offset) {
	/* StepMania uses measures instead of offsets, which makes it complicated
	
		Firstly, you have an offset, given as seconds, this is the audio offset.
		So the first measure will start from here, even if it's negative.

		#BPMS:0.000=102.769
		,6.000=113.212 Notice we have an extra comma here, we need to
		,7.000=113.208 get rid of it using a find_first_of
		,8.000=115.475
		,9.000=115.470
	*/

	offset *= TimedObject::UnitScale::second; // offset is given as seconds;

	auto split = [](const std::string& str) -> std::pair<double, double> {
		size_t sep_loc = str.find('=');
		return std::make_pair<double, double>(
			std::stod(str.substr(
				// Refer to docstring comment
				str.find_first_of(',') == std::string::npos ? 0 : 1,
				sep_loc)),
			std::stod(str.substr(sep_loc + 1)));
	};

	auto bpmToLength = [](const double& bpm) -> double { // each increment represents a beat
		return (1 / bpm) * TimedObject::UnitScale::minute;
	};

	std::vector<std::pair<double, double>> bpm_pair_v;
	
	// {Measure=BPM},{Measure=BPM, ... }
	// {{Measure, BPM}, {Measure, BPM}, ... }
	std::transform(begin, end, std::back_inserter(bpm_pair_v), split);	

	double measure_no_prev = 0.0;
	double measure_length_prev = 0.0;
	double measure_no_curr = 0.0;
	double measure_length_curr = 0.0;

	// Generate Timing Points from pairs
	for (const auto & pair : bpm_pair_v) {
		measure_no_curr = pair.first;
		measure_length_curr = bpmToLength(pair.second);

		offset += measure_length_prev *
			(measure_no_curr - measure_no_prev);
		TimingPointSM tp = TimingPointSM(offset, pair.second, 4, 4);
		SPtrTimedObject sptr = std::make_shared<TimingPointSM>(tp);
		eo_v_->push_back(sptr);

		measure_no_prev = measure_no_curr;
		measure_length_prev = measure_length_curr;
	}

	return std::move(bpm_pair_v);
}

void VsrgMapSM::processStops(const std::vector<std::string>::iterator & begin,
							 const std::vector<std::string>::iterator & end) {
	// Pending Implementation, not sure how this one works
}

void VsrgMapSM::processHO(std::vector<std::string>::iterator begin,
	const std::vector<std::string>::iterator & end,
	const std::vector<std::pair<double, double>> & bpm_pair_v) {

	std::vector<std::string> chunk = {};

	unsigned int index_pair = 0;
	double curr_bpm = bpm_pair_v[index_pair].first;
	double curr_measure = bpm_pair_v[index_pair].second;

	auto getNext = [&bpm_pair_v, &index_pair, &curr_bpm, &curr_measure]() {
		try { 
			auto index_next = index_pair;
			if (curr_measure >= bpm_pair_v[index_next].first) {
				curr_measure = bpm_pair_v[index_next].first;
				curr_bpm = bpm_pair_v[index_next].second;
			}
		}
		catch (...) {} // Means there's no next 
	};

	// Can we get the offset?



	for (unsigned int index_row = 0; begin < end; begin++, index_row++) {
		if (begin->back() == ',') { // Found end of measure
			processHOMeasure(chunk.begin(), chunk.end(), index_row, chunk.size());
			chunk.clear();
			curr_measure += 1;
		}
		else chunk.push_back(*begin);
	}
}

void VsrgMapSM::processHOMeasure(std::vector<std::string>::iterator begin, 
							   const std::vector<std::string>::iterator& end,
							   unsigned int index,
							   size_t chunk_size){
	unsigned int i = 0;	

}

std::unordered_map<std::string, std::vector<std::string>> VsrgMapSM::toUMap(
	std::vector<std::string>::const_iterator& begin,
	std::vector<std::string>::const_iterator end) {
	std::unordered_map<std::string, std::vector<std::string>> u_map = {};
	std::string str = "";
	std::string key = "";
	std::vector<std::string> value = {};
	size_t str_sep = 0;
	for (; begin != end; begin++) {
		if (begin->front() == '/') continue; // Ignore comments
		value = {};
		str = *begin;
		str_sep = str.find(':');
		key = str.substr(0, str_sep);

		// If KEY:VALUE;
		if (str.back() == ';')
			value.push_back(str.substr(str_sep + 1, str.length() - str_sep - 2));
		else { // Else KEY:VALUE\nVALUE\n...\n;
			// Still need to push the first value in (KEY:VALUE)
			value.push_back(str.substr(str_sep + 1)); begin++;
			for (; begin != end && *begin != ";"; begin++) {
				value.push_back(*begin);
			}
		}
		u_map[key] = value;
	}
	return std::move(u_map);
}
