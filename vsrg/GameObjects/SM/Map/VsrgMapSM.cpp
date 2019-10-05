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
	processHO(notes_str.begin() + 6, notes_str.end(), bpm_pairs, params.offset_);

}

void VsrgMapSM::saveFile(const std::string& file_path, bool overwrite) {

}

std::vector<std::pair<double, double>>
VsrgMapSM::processBpms(const std::vector<std::string>::iterator& begin,
					   const std::vector<std::string>::iterator & end,
					   double offset) {
	/* StepMania uses measures instead of offsets, which makes it complicated
	
		Firstly, you have an offset, given as seconds, this is the audio offset.
		So the first beat will start from here, even if it's negative.

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

	std::vector<std::pair<double, double>> bpm_pair_v;
	
	// {Measure=BPM},{Measure=BPM, ... }
	// {{Measure, BPM}, {Measure, BPM}, ... }
	std::transform(begin, end, std::back_inserter(bpm_pair_v), split);	

	//double measure_no_prev = 0.0;
	//double measure_length_prev = 0.0;
	//double measure_no_curr = 0.0;
	//double measure_length_curr = 0.0;

	//// Generate Timing Points from pairs
	//for (const auto & pair : bpm_pair_v) {
	//	measure_no_curr = pair.first;
	//	measure_length_curr = bpmToLength(pair.second);

	//	offset += measure_length_prev *
	//		(measure_no_curr - measure_no_prev);
	//	TimingPointSM tp = TimingPointSM(offset, pair.second, 4, 4);
	//	SPtrTimedObject sptr = std::make_shared<TimingPointSM>(tp);
	//	eo_v_->push_back(sptr);

	//	measure_no_prev = measure_no_curr;
	//	measure_length_prev = measure_length_curr;
	//}

	return std::move(bpm_pair_v);
}

void VsrgMapSM::processStops(const std::vector<std::string>::iterator & begin,
							 const std::vector<std::string>::iterator & end) {
	// Pending Implementation, not sure how this one works
}

void VsrgMapSM::processHO(std::vector<std::string>::iterator begin,
	const std::vector<std::string>::iterator& end,
	const std::vector<std::pair<double, double>>& bpm_pair_v,
	double offset) {

	// Pushes Timing Point to EOV
	auto pushToEOV = [this](double offset, double bpm) {
		TimingPointSM tp = TimingPointSM(offset, bpm, 4, 4);
		SPtrTimedObject sptr = std::make_shared<TimingPointSM>(tp);
		eo_v_->push_back(sptr);
	};

	std::vector<std::string> beat_chunk = {};

	int beat = 0;
	unsigned int size = 0;
	unsigned int bpm_pair_i = 0;
	double beat_length = 0;
	double bpm = bpm_pair_v[0].second; pushToEOV(offset, bpm);

	auto bpmToBeat = [](const double& bpm) -> double {
		return (1 / bpm) * TimedObject::UnitScale::minute;
	};

	// Tries to update bpm based on current beat
	auto tryUpdateBpm = [&bpm_pair_v, &bpm, &bpm_pair_i,
						 pushToEOV, this, &offset](double beat){
		try {
			auto next_beat = bpm_pair_v[bpm_pair_i + 1].first;
			if (beat >= next_beat) {
				bpm_pair_i++;
				bpm = bpm_pair_v[bpm_pair_i].second;
				pushToEOV(offset, bpm);
			}
		}
		catch (...) { // Means the beat is still on the same bpm
			// Catches out of index searching
		}
	};

	for (unsigned int index_row = 0; begin < end; begin++, index_row++) {
		if (begin->back() == ',') { // Found end of beat
			/*  
				Now we have the data of a beat

				We have to find out:
				1. offset of the start of the beat
				2. bpm
				3. size
			*/

			tryUpdateBpm(beat); // Tries to update bpm w.r.t. beat

			beat_length = bpmToBeat(bpm); // How long the beat lasts in ms
			size = beat_chunk.size(); // Size of chunk vector
			
			processHOBeat(beat_chunk.begin(), beat_chunk.end(),
						  offset, beat_length / size);

			/*
				After parsing the beat

				We need to:
				1. push the offset to the end of the beat
				2. clear the beat_chunk
			
			*/

			offset += beat_length;
			beat++;
			beat_chunk.clear();
		}
		else beat_chunk.push_back(*begin);
	}
}

void VsrgMapSM::processHOBeat(std::vector<std::string>::iterator begin, 
							  const std::vector<std::string>::iterator& end,
							  double offset,
							  double step_size){
	/*
		Step Size: Determines the offset movement for 1 step

		0001 [0ms] <offset = 0ms>
		0100 [0 + step_size ms]
		0000 [0 + 2 * step_size ms]
		...
	
	*/
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
