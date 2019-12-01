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

const double VsrgMapSM::SNAP_ERROR_MARGIN = 0.3;

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
	params.offset_	                    = std::stod(getValue("#OFFSET")[0]) * TimedObject::Units::second;
	std::vector<std::string> bpm_str	=			getValue("#BPMS");
	std::vector<std::string> stop_str	=			getValue("#STOPS");
	params.display_bpm_					=			getValue("#DISPLAYBPM")[0];
	//NULL								=			getValue("#BGCHANGES:")[0];
	//NULL								=			getValue("#FGCHANGES:")[0];

	std::vector<std::string> notes_str	=			getValue("#NOTES")	; // Move it to #NOTES	

	params.chart_type_		=	notes_str[2]; params.chart_type_		.pop_back();
	params.group_			=	notes_str[3]; params.group_				.pop_back();
	params.difficulty_name_ =	notes_str[4]; params.difficulty_name_	.pop_back();
	params.difficulty_val_	=	notes_str[5]; params.difficulty_val_	.pop_back();

	auto bpm_pairs = processBpms(bpm_str.begin(), bpm_str.end());
	processStops(stop_str.begin(), stop_str.end());
	processObjs(notes_str.begin() + 6, notes_str.end(), bpm_pairs, params.offset_);

}

void VsrgMapSM::saveFile(const std::string& file_path, bool overwrite) {

	/*
		We have to settle how notes and bpm are interlinked here

		- We cannot assume perfect offset synchronization
		- BPM goes by beats, but notes go by measures.
		  We can assume that all measures have 4 beats.

		Steps:
		- We will first set a snap threshold, that is, if a note is within
		  a set range, it will be regarded as a specific snap. This is
		  proportional to how many divisions we want to use.
		  We will use 192nds to be safe, it is the maximum anyways

		- We generate all possible 192nds as we go through the TPs, if we
		  notice that a note is in between 2 192nds, we will assign the note
		  to the closest 192nd!

		- We will have to trim the output since not all beats require 192nd
	*/

	std::vector<Bpm> bpms;
	std::vector<Note> notes;

	{ // Limit scope to avoid pollution
		auto tp_v = eo_v_->getClassOnly<TimingPointSM>();
		for (const auto& tp : tp_v) {
			bpms.push_back(Bpm(tp.getOffset(), tp.getBpm()));
		}
		auto rn_v = ho_v_->getClassOnly<RollNoteSM>();
		for (const auto& rn : rn_v) {
			notes.push_back(Note(rn.getOffset(), rn.getIndex(), RollNoteSM::chr_head));
			notes.push_back(Note(rn.getOffsetEnd(), rn.getIndex(), RollNoteSM::chr_tail));
		}
		auto hn_v = ho_v_->getClassOnly<HoldNoteSM>();
		for (const auto& hn : hn_v) {
			notes.push_back(Note(hn.getOffset(), hn.getIndex(), HoldNoteSM::chr_head));
			notes.push_back(Note(hn.getOffsetEnd(), hn.getIndex(), HoldNoteSM::chr_tail));
		}
		auto mn_v = ho_v_->getClassOnly<MineNoteSM>();
		for (const auto& mn : mn_v) {
			notes.push_back(Note(mn.getOffset(), mn.getIndex(), MineNoteSM::chr));
		}
		auto nn_v = ho_v_->getClassOnly<NormalNoteSM>();
		for (const auto& nn : nn_v) {
			notes.push_back(Note(nn.getOffset(), nn.getIndex(), NormalNoteSM::chr));
		}
	}

	std::sort(notes.begin(), notes.end(), [](Note i, Note j) { return i.offset < j.offset; });
	std::sort(bpms.begin(), bpms.end(),   [](Bpm i, Bpm j)   { return i.offset < j.offset; });

	// We will create a large 2D Vector filled with '0's
	// Then we will populate that
		
	// Initialize a 3D Vector [frame_i][row][column]
	std::vector<std::vector<std::vector<char>>> chart
		(0, std::vector<std::vector<char>>(192, std::vector<char>(4)));
	
	// We will populate this subframe then push to the main frame once it's filled
	std::vector<std::vector<char>> measure
		(192, std::vector<char>(4, '0'));

	auto bpm_it = bpms.begin();
	auto note_it = notes.begin();
	auto offset = bpm_it->offset;
	int measure_row = 0;
	double step_size = 60000. / (bpm_it->bpm * 48.); // 1/48 beat sensitivity
	auto moveOffset = [&offset, &measure_row](double step_size) {
		offset += step_size;
		measure_row++;
	};
	auto updateBpm = [&offset, &bpm_it, &bpms, &step_size]() {
		if (bpm_it + 1 == bpms.end()) {
			bpm_it++;
		}
		else if (offset >= (bpm_it + 1)->offset - SNAP_ERROR_MARGIN) {
			bpm_it++;
			step_size = 60000. / (bpm_it->bpm * 48.);
			offset = bpm_it->offset; // Fixes offset
		}
		return;
	};
	auto pushMeasure = [&measure, &chart, &measure_row]() {
		// Optimize the 3D Vector before pushing

		auto measure_ = measure; // This holds the temp frame
		bool optimize_flag = false;

		// 10 10 10 10 -> 1111
		// We stop at 6ths (192 isn't just 2^x)
		while (measure_.size() > 12 && !optimize_flag) {
			for (int _ = measure.size() - 1; _ > 0; _ -= 2) {
				if (measure[_] == std::vector<char>(4, '0'))
					measure_.erase(measure_.begin() + _);
				else {
					optimize_flag = true; break;
				}
			}
			measure = measure_;
		}

		// 100 100 100 100 -> 1111 
		optimize_flag = false;
		for (int _ = measure.size() - 1; _ > 0; _ -= 3) {
			if (measure[_] == std::vector<char>(4, '0') &&
				measure[_ - 1] == std::vector<char>(4, '0')) {
				measure_.erase(measure_.begin() + _);
				measure_.erase(measure_.begin() + _ - 1);
			}
			else {
				optimize_flag = true; break;
			}
		}

		// If we break half way through we don't override
		if (!optimize_flag) measure = measure_;

		measure_row = 0; // Reset measure index
		chart.push_back(measure);
		measure = std::vector<std::vector<char>>(192, std::vector<char>(4, '0'));
	};

	while (bpm_it < bpms.end()) {
		for (int beat = 0; beat < 4; beat++) {
			for (int step = 0; step < 48;) {
				if (note_it != notes.end() &&
					note_it->offset >= offset - SNAP_ERROR_MARGIN &&
					note_it->offset <= (offset + step_size) - SNAP_ERROR_MARGIN) {
					measure[measure_row][note_it->index] = note_it->chr;
					note_it++;
					// There may be multiple on the same step, we don't increment it
				}
				else {
					moveOffset(step_size);
					step++;
				}
			}
			updateBpm();
			if (bpm_it == bpms.end()) break;
		}
		pushMeasure();
	}

	std::vector<std::string> contents = {};
	auto _ = [&contents](const std::string & str) { contents.push_back(str); };

	_("[General]"); 
	_("#TITLE:" + params.title_);
	_("#SUBTITLE:" + params.subtitle_);
	_("#ARTIST:" + params.artist_);
	_("#TITLETRANSLIT:" + params.title_u_);
	_("#SUBTITLETRANSLIT:" + params.subtitle_u_);
	_("#ARTISTTRANSLIT:" + params.artist_u_);
	_("#GENRE:" + params.genre_);
	_("#CREDIT:" + params.creator_);
	_("#MUSIC:" + params.audio_path_);
	_("#BANNER:" + params.bn_path_);
	_("#BACKGROUND:" + params.bg_path_);
	_("#LYRICSPATH:");											
	_("#CDTITLE:" + params.cd_path_);
	_("#SAMPLESTART:" + std::to_string(params.preview_time_start_));
	_("#SAMPLELENGTH:" + std::to_string(params.preview_time_end_));
	_("#SELECTABLE");											
	_("#OFFSET:" + std::to_string(params.offset_));	
	_("#BPMS:");// +std::vector<std::string> bpm_str	);
	_("#STOPS:"); // +std::vector<std::string> stop_str	);
	_("#DISPLAYBPM:" + params.display_bpm_);
	_("#BGCHANGES:");
	_("#FGCHANGES:");
	_("//--------------- dance-single -  ----------------");
	_("#NOTES:");
	_(params.chart_type_);
	_(params.group_);
	_(params.difficulty_name_);
	_(params.difficulty_val_);
	_("     0,0,0,0,0:");
	
	for (const auto& measure : chart) {
		for (const auto& step : measure) {
			std::string s = "";
			for (const char& str : step) s += str;
			_(s);
		}
		_(",");
	}
	writeFile(contents, file_path, overwrite);
}

std::vector<VsrgMapSM::Bpm>
VsrgMapSM::processBpms(const std::vector<std::string>::iterator& begin,
					   const std::vector<std::string>::iterator& end) {
	/* StepMania uses measures instead of offsets, which makes it complicated
	
		Firstly, you have an offset, given as seconds, this is the audio offset.
		So the first beat will start from here, even if it's negative.

		#BPMS:0.000=102.769
		,6.000=113.212 Notice we have an extra comma here, we need to
		,7.000=113.208 get rid of it using a find_first_of
		,8.000=115.475
		,9.000=115.470
	*/
	auto split = [](const std::string& str) -> Bpm {
		size_t sep_loc = str.find('=');
		return Bpm(
			// Refer to docstring comment
			std::stod(str.substr( // Offset
				str.find_first_of(',') == std::string::npos ? 0 : 1, sep_loc)),
			std::stod(str.substr(sep_loc + 1))); // Bpm
	};

	std::vector<Bpm> bpm_pair_v;
	
	// {Measure=BPM},{Measure=BPM, ... }
	// {{Measure, BPM}, {Measure, BPM}, ... }
	std::transform(begin, end, std::back_inserter(bpm_pair_v), split);	

	return std::move(bpm_pair_v);
}

void VsrgMapSM::processStops(const std::vector<std::string>::iterator & begin,
							 const std::vector<std::string>::iterator & end) {
	// Pending Implementation, not sure how this one works
}

void VsrgMapSM::processObjs(
	std::vector<std::string>::iterator begin,
	const std::vector<std::string>::iterator& end,
	const std::vector<Bpm>& bpm_pair_v,
	double offset) {

	/* Processing HO and EO in parellel
	
	This is a pretty complicated process, I'll explain briefly

	Here are a few pointers:
	- BPM is labelled in BEATS
	- Notes are separated by MEASURES with ','
	- It is ineffecient and bulky to process both in series
	
	What we aim to do here is to have an already processed BPM pair
	vector in the format: {Measure:BPM},{Measure,BPM},...

	For each measure, we split it into 4 (it must be 4). Then we
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

	std::vector<std::string> measure = {};

	int beat = 0;
	unsigned int size = 0;
	unsigned int bpm_pair_i = 0;
	double beat_length = 0;
	double bpm = bpm_pair_v[0].bpm; pushToEOV(offset, bpm);

	// Tries to update bpm based on current beat
	auto updateBpm = [&bpm_pair_v, &bpm, &bpm_pair_i, &offset,
					  pushToEOV, this](double beat){

		// First if to prevent out of index
		if (bpm_pair_i + 1 >= bpm_pair_v.size()) return;

		auto next_beat = bpm_pair_v[bpm_pair_i + 1].offset;
		if (beat >= next_beat) { // Check if we need to update bpm
			bpm_pair_i++;
			bpm = bpm_pair_v[bpm_pair_i].bpm;
			pushToEOV(offset, bpm);
		}
		// Else means the beat is still on the same bpm
	};

	for (unsigned int index_row = 0; begin < end; begin++, index_row++) {
		if (begin->back() == ',' || begin == (end - 1)) { // Found end of measure
			/*  Measure 1, Size 8
				0000 Beat 1 (8th, 1/2) [1]
				0000		(8th, 2/2) [2]
				0000 Beat 2	(8th, 1/2)
				0000		(8th, 2/2)
				0000 Beat 3	(8th, 1/2)
				0000		(8th, 2/2)
				0000 Beat 4	(8th, 1/2)
				0000		(8th, 2/2)
			*/

			size = measure.size(); // Size of chunk vector

			// Each chunk has 4 beats, so we split them into 4 and loop
			for (int _ = 0; _ < 4; _++) {
				updateBpm(beat); // Tries to update bpm w.r.t. beat
				
				beat_length = TimedObject::Units::bpmToMspb(bpm); // How long the beat lasts in ms

				processHOBeat(
					measure.begin() + (int)  _      * size / 4, // Start Beat
					measure.begin() + (int) (_ + 1) * size / 4, // End Beat
					offset,	
					beat_length * 4 / size); // Step Size

				// Push offset to end of beat
				offset += beat_length;
				beat++;
			}
			measure.clear();
		}
		// If we do not find end of beat we feed it to chunk
		else measure.push_back(*begin); 
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
		case NormalNoteSM::chr: {
			auto nn = NormalNoteSM(offset, index);
			sptr = std::make_shared<NormalNoteSM>(nn);
			ho_v_->push_back(sptr);
			break;
		}
		case HoldNoteSM::chr_head: { // Buffer Head
			auto hn = HoldNoteSM(offset, index, 0);
			sptr_buffer[index] = std::make_shared<HoldNoteSM>(hn);
			break;
		}
		case HoldNoteSM::chr_tail: { // Buffer Tail
			if (auto ln = sptr_buffer[index]) {
				ln->setLength(offset - ln->getOffset());
				ho_v_->push_back(ln);
				sptr_buffer[index] = nullptr; // Clear buffer
			} else {
				BOOST_ASSERT_MSG(true, "Tail found without Head");
			}
			break;
		}
		case RollNoteSM::chr_head: { // Buffer Head
			auto hn = RollNoteSM(offset, index, 0);
			sptr_buffer[index] = std::make_shared<RollNoteSM>(hn);
			break;
		}
		case MineNoteSM::chr: {
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

	// For each row we will split it further into parsing each char
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
