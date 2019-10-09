#include "stdafx.h"
#include "VsrgMapSM.h"
#include "GameObjects/SM/Singular/Event/TimingPointSM.h"
#include "GameObjects/SM/Singular/Event/StopPointSM.h"
#include "GameObjects/SM/Multiple/EventObjectVectorSM.h"
#include "GameObjects/SM/Multiple/HitObjectVectorSM.h"
#include "GameObjects/SM/Singular/Hit/NormalNoteSM.h"
#include "GameObjects/SM/Singular/Hit/RollNoteSM.h"
#include "GameObjects/SM/Singular/Hit/MineNoteSM.h"
#include "GameObjects/SM/Singular/Hit/HoldNoteSM.h"

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

	/* Processing HO and EO in parellel
	
	This is a pretty complicated process, I'll explain briefly

	Here are a few pointers:
	- BPM is labelled in BEATS
	- Notes are separated by MEASURES with ','
	- It is ineffecient and bulky to process both in series
	
	What we aim to do here is to have an already processed BPM pair
	vector in the format: {Measure:BPM},{Measure,BPM},...

	Then we read the Notes by chunk. A chunk is defined by if the notes
	are wrapped in between those ','. This defines a measure_chunk.

	For each measure_chunk, we split it into 4 (it must be 4). Then we
	feed it into tryUpdateBPM.

	tryUpdateBPM:
		This lambda tries to update the bpm if the current beat enters
		a new defined BPM. If not it just does nothing.
		Updating the bpm is important to get the correct offset, which
		is explained below

	The updated bpm, computes a beat_length, this is to update the
	offset, to correct the newer BPM labels.

	This process is then repeated until we read all BPM inputs.
	*/


	// Pushes Timing Point to EOV
	auto pushToEOV = [this](double offset, double bpm) {
		TimingPointSM tp = TimingPointSM(offset, bpm, 4, 4);
		SPtrTimedObject sptr = std::make_shared<TimingPointSM>(tp);
		eo_v_->push_back(sptr);
	};

	std::vector<std::string> measure_chunk = {};

	int beat = 0;
	unsigned int size = 0;
	unsigned int bpm_pair_i = 0;
	double beat_length = 0;
	double bpm = bpm_pair_v[0].second; pushToEOV(offset, bpm);

	auto bpmToBeat = [](const double& bpm) -> double {
		return (1 / bpm) * TimedObject::UnitScale::minute;
	};

	// Tries to update bpm based on current beat
	auto updateBpm = [&bpm_pair_v, &bpm, &bpm_pair_i, &offset,
						 pushToEOV, this](double beat){
		// First if to prevent out of index
		if (bpm_pair_i + 1 < bpm_pair_v.size()) {
			auto next_beat = bpm_pair_v[bpm_pair_i + 1].first;
			if (beat >= next_beat) {
				bpm_pair_i++;
				bpm = bpm_pair_v[bpm_pair_i].second;
				pushToEOV(offset, bpm);
			}
			// Else means the beat is still on the same bpm
		}
	};

	for (unsigned int index_row = 0; begin < end; begin++, index_row++) {
		if (begin->back() == ',' || begin == (end - 1)) { // Found end of beat
			/*  
				Now we have the data of a beat

				We have to find out:
				1. offset of the start of the beat
				2. bpm
				3. size
			*/

			size = measure_chunk.size(); // Size of chunk vector

			// Each chunk has 4 beats, so we split them into 4 and loop
			for (int _ = 0; _ < 4; _++) {

				updateBpm(beat); // Tries to update bpm w.r.t. beat
				
				beat_length = bpmToBeat(bpm); // How long the beat lasts in ms

				processHOBeat(
					measure_chunk.begin() + (int)  _      * size / 4,
					measure_chunk.begin() + (int) (_ + 1) * size / 4,
					offset,
					beat_length * 4 / size);

				// Push offset to end of beat
				offset += beat_length;
				beat++;
			}
			measure_chunk.clear();
		}
		// If we do not find end of beat we feed it to chunk
		else measure_chunk.push_back(*begin); 
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
	auto createHO = [&begin, this](unsigned int index, char chr, double offset)
	{
		/* Function of sptr_buffer

			Some Objects need 2 inputs for it to be "complete", the buffer
			holds old inputs so that the final inputs can "complete" it
			and push into ho_v_.

			Remember to clear the buffer!
		*/

		static std::vector<std::shared_ptr<LongNote>> sptr_buffer(begin->size(), nullptr);
		SPtrHitObject sptr = nullptr;
		switch (chr)
		{
		case '0': break;
		case '1': {
			auto nn = NormalNoteSM(offset, index);
			sptr = std::make_shared<NormalNoteSM>(nn);
			ho_v_->push_back(sptr);
			break;
		}
		case '2': { // Buffer Head
			auto hn = HoldNoteSM(offset, index, 0);
			sptr_buffer[index] = std::make_shared<HoldNoteSM>(hn);
			break;
		}
		case '3': { // Buffer Tail
			if (auto ln = sptr_buffer[index]) {
				ln->setLength(offset - ln->getOffset());
				ho_v_->push_back(ln);
				sptr_buffer[index] = nullptr; // Clear buffer
			} else {
				BOOST_ASSERT_MSG(true, "Tail found without Head");
			}
			break;
		}
		case '4': { // Buffer Head
			auto hn = RollNoteSM(offset, index, 0);
			sptr_buffer[index] = std::make_shared<RollNoteSM>(hn);
			break;
		}
		case 'M': {
			auto mn = MineNoteSM(offset, index);
			sptr = std::make_shared<MineNoteSM>(mn);
			ho_v_->push_back(sptr);
			break;
		}
		// There are still more note types, will implement later			
		default:
			// All unknown types fall here
			break;
		}
	};

	for (; begin < end; begin++) {
		std::string row = *begin;
		for (size_t index = 0; index < row.size(); index++) {
			createHO(index, row[index], offset);
		}
		offset += step_size;
	}

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
