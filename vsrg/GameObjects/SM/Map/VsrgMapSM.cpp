#include "stdafx.h"
#include "VsrgMapSM.h"

void VsrgMapSM::loadFile(const std::string& file_path) {
	// Reference: https://github.com/stepmania/stepmania/wiki/sm

	std::vector<std::string> file_contents = readFile(file_path);

	std::vector<std::string>::const_iterator it = file_contents.cbegin();
	std::vector<std::string>::const_iterator ite = file_contents.cend();

	auto u_map = toUMap(it, ite);

	/* // Moves iter to tag
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
	};*/

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

	params.chart_type_		=			notes_str[2]; params.chart_type_		.pop_back();
	params.group_			=			notes_str[3]; params.group_				.pop_back();
	params.difficulty_name_ =			notes_str[4]; params.difficulty_name_	.pop_back();
	params.difficulty_val_	=			notes_str[5]; params.difficulty_val_	.pop_back();

	processBpms(bpm_str, params.offset_);
	processStops(stop_str, eo_v_);

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
			value.push_back(str.substr(str_sep + 1));
			for (; begin != end && *begin != ";"; begin++) {
				value.push_back(*begin);
			}
		}
		
		u_map[key] = value;
	}
	return std::move(u_map);
}
