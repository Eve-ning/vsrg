#include "stdafx.h"
#include "VsrgMapSM.h"

void VsrgMapSM::loadFile(const std::string& file_path) {
	// Reference: https://github.com/stepmania/stepmania/wiki/sm

	std::vector<std::string> file_contents = readFile(file_path);

	// To convert to using boost::qi when im not lazy

	std::vector<std::string>::const_iterator it = file_contents.cbegin();
	std::vector<std::string>::const_iterator ite = file_contents.cend();

	// Moves iter to tag
	auto iterToTag = [](
		std::vector<std::string>::const_iterator& begin,
		std::vector<std::string>::const_iterator end,
		const std::string& starts_with) -> std::vector<std::string> {
			auto begin_input = begin;
			std::vector<std::string> str_v = {};

			// Iterate through the vector
			for (; begin != end; begin++) {
				// If we find a starts_with match
				if (boost::algorithm::starts_with(*begin, starts_with)) {
					// Substrings KEY:(VALUE)
					std::string value = *begin;
					value = value.substr(value.find(':') + 1);

					// Push back (VALUE)
					str_v.push_back(value);

					// Case: VALUE;
					if (begin->back() == ';') {
						str_v[0].pop_back(); // Remove the ';'
						return str_v;
					}

					// Case: VALUE\nVALUE\n...\n;
					else {
						for (; begin->back() != ';'; begin++)
							str_v.push_back(*begin);
						return str_v;
					}
				}
			}

			// If we reach here, condition was never true
			begin = begin_input;
			return std::vector<std::string>({ "" });
	};

	#define MATCH(str) iterToTag(it, ite, str)

	params.title_						=			MATCH("#TITLE:")[0];
	params.subtitle_					=			MATCH("#SUBTITLE:")[0];
	params.artist_						=			MATCH("#ARTIST:")[0];
	params.title_u_						=			MATCH("#TITLETRANSLIT:")[0];
	params.subtitle_u_					=			MATCH("#SUBTITLETRANSLIT:")[0];
	params.artist_u_					=			MATCH("#ARTISTTRANSLIT:")[0];
	params.genre_						=			MATCH("#GENRE:")[0];
	params.creator_						=			MATCH("#CREDIT:")[0];
	params.audio_path_					=			MATCH("#MUSIC:")[0];
	params.bn_path_						=			MATCH("#BANNER:")[0];
	params.bg_path_						=			MATCH("#BACKGROUND:")[0];
	//NULL								=			MATCH("#LYRICSPATH:");
	params.cd_path_						=			MATCH("#CDTITLE:")[0];
	params.preview_time_start_			= std::stod(MATCH("#SAMPLESTART:")[0]);
	params.preview_time_end_			= std::stod(MATCH("#SAMPLELENGTH:")[0]) + params.preview_time_start_;
	//NULL								=			MATCH("#SELECTABLE:");
	params.offset_						= std::stod(MATCH("#OFFSET:")[0]);
	std::vector<std::string> bpm_str	=			MATCH("#BPMS:");
	std::vector<std::string> stop_str	=			MATCH("#STOPS:");
	params.display_bpm_					=			MATCH("#DISPLAYBPM:")[0];
	//NULL								=			MATCH("#BGCHANGES:");
	//NULL								=			MATCH("#FGCHANGES:");

	std::vector<std::string> notes_str	=			MATCH("#NOTES:"); // Move i	t to #NOTES	
	#undef MATCH

	#define TRIM(str) str.erase(remove_if(str.begin(), str.end(), isspace), str.end());

	TRIM(notes_str[2]);
	TRIM(notes_str[3]);
	TRIM(notes_str[4]);
	TRIM(notes_str[5]);

	#undef TRIM(str)

	params.chart_type_		=			notes_str[2]; params.chart_type_		.pop_back();
	params.group_			=			notes_str[3]; params.group_				.pop_back();
	params.difficulty_name_ =			notes_str[4]; params.difficulty_name_	.pop_back();
	params.difficulty_val_	= std::stod(notes_str[5].substr(0, notes_str[4].size() - 1));

	// TODO: PARSE BPMS
	processBpms(bpm_str, params.offset_);
	processStops(stop_str, eo_v_);

	// TODO: PARSE NOTES
	std::vector<std::string> notes = IterHelper::getBetween(++it, ite);

}

void VsrgMapSM::saveFile(const std::string& file_path, bool overwrite) {

}

void VsrgMapSM::readHO(const std::vector<std::string>& ho_v, const SPtrEventObjectVector eo_v) {
	std::vector<std::string> chunk = {};
	auto it = ho_v.begin();
	auto ite = ho_v.end();

	for (; it < ite; it++) {
		if (it->back() == ',') {
			readHOChunk(chunk);
			chunk.clear();
		}
		else chunk.push_back(*it);
	}
}

void VsrgMapSM::readHOChunk(const std::vector<std::string>& str_v) {
	size_t size = str_v.size(); // This determines the snap
}

void VsrgMapSM::processBpms(const std::vector<std::string>& str_v, double offset) {

}

void VsrgMapSM::processStops(const std::vector<std::string>& str_v, SPtrEventObjectVector eo_v) {

}
