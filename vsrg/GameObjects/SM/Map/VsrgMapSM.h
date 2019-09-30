#pragma once
#include "BaseObjects/Map/VsrgMap.h"
#include "GameObjects/SM/Map/VsrgMapSMParams.h"
#include "Helpers/MiscHelper.h"
class VsrgMapSM : public VsrgMap
{	
public:
	VsrgMapSM() {}
	~VsrgMapSM() {}

	virtual void loadFile(const std::string & file_path) override {
		// Reference: https://github.com/stepmania/stepmania/wiki/sm

		using namespace IterHelper;
		std::vector<std::string> file_contents = readFile(file_path);

		// To convert to using boost::qi when im not lazy

		std::vector<std::string>::const_iterator it = file_contents.cbegin();
		std::vector<std::string>::const_iterator ite = file_contents.cend();

		params.title_				= matchTag(it, ite, "#TITLE:");
		params.subtitle_			= matchTag(it, ite, "#SUBTITLE:");
		params.artist_				= matchTag(it, ite, "#ARTIST:");
		params.title_u_				= matchTag(it, ite, "#TITLETRANSLIT:");
		params.subtitle_u_			= matchTag(it, ite, "#SUBTITLETRANSLIT:");
		params.artist_u_			= matchTag(it, ite, "#ARTISTTRANSLIT:");
		params.genre_				= matchTag(it, ite, "#GENRE:");
		params.creator_				= matchTag(it, ite, "#CREDIT:");
		params.bn_path_				= matchTag(it, ite, "#BANNER:");
		params.bg_path_				= matchTag(it, ite, "#BACKGROUND:");
		//NULL						= matchTag(it, ite, "#LYRICSPATH:");
		params.cd_path_				= matchTag(it, ite, "#CDTITLE:");
		params.audio_path_			= matchTag(it, ite, "#MUSIC:");
		double offset				= std::stod(matchTag(it, ite, "#OFFSET:"));
		std::string bpm_str			= matchTag(it, ite, "#BPMS:");
		std::string stop_str		= matchTag(it, ite, "#STOPS:");
		params.preview_time_start_	= std::stod(matchTag(it, ite, "#SAMPLESTART:"));
		params.preview_time_end_	= std::stod(matchTag(it, ite, "#SAMPLELENGTH:"));
		params.display_bpm_			= matchTag(it, ite, "#DISPLAYBPM:");
		//NULL						= matchTag(it, ite, "#SELECTABLE:");
		//NULL						= matchTag(it, ite, "#BGCHANGES:");
		//NULL						= matchTag(it, ite, "#FGCHANGES:");

		matchTag(it, ite, "#NOTES:"); // Move it to #NOTES	
		params.chart_type_		= *(++it);
		// If creator is empty we assign the it, else we still increment it
		if (params.creator_.empty()) 
			params.creator_		= *(++it); else ++it;
		params.difficulty_name_ = *(++it);
		params.difficulty_val_	= std::stod(*(++it));


		// TODO: PARSE NOTES

	}
	virtual void saveFile(const std::string & file_path, bool overwrite = false) override {

	}

	VsrgMapSMParams params;
};

