#include "stdafx.h"
#include "VsrgMapOsu.h"
#include "Helpers/MiscHelper.h"
#include "BaseObjects/Singular/Hit/HitObject.h"
#include "BaseObjects/Singular/Event/EventObject.h"
#include "GameObjects/Osu/Singular/Hit/NormalNoteOsu.h"
#include "GameObjects/Osu/Singular/Hit/LongNoteOsu.h"
#include "GameObjects/Osu/Singular/Event/ScrollPointOsu.h"
#include "GameObjects/Osu/Singular/Event/TimingPointOsu.h"
#include "GameObjects/Osu/Multiple/HitObjectVectorOsu.h"
#include "GameObjects/Osu/Multiple/EventObjectVectorOsu.h"
#include <boost/spirit/include/classic.hpp>

VsrgMapOsu::VsrgMapOsu()
{
	auto eo = EventObjectVectorOsu();
	auto ho = HitObjectVectorOsu();
	eo_v_ = std::make_shared<EventObjectVectorOsu>(eo);
	ho_v_ = std::make_shared<HitObjectVectorOsu>(ho);
}

VsrgMapOsu::~VsrgMapOsu()
{
}

void VsrgMapOsu::loadFile(const std::string & file_path) {
	using namespace IterHelper;
	using namespace boost::spirit::classic;
	

	std::vector<std::string> file_contents = readFile(file_path);
	
	std::vector<std::string>::const_iterator it = file_contents.cbegin();
	std::vector<std::string>::const_iterator ite = file_contents.cend();

	params.audio_file_name_ =				   matchTag(it, ite, "AudioFilename:");
	params.preview_time_	=		 std::stoi(matchTag(it, ite, "PreviewTime:"));
	params.bookmarks_		= processBookmarks(matchTag(it, ite, "Bookmarks:"));
	params.title_			=				   matchTag(it, ite, "Title:");
	params.title_u_			=				   matchTag(it, ite, "TitleUnicode:");
	params.artist_			=				   matchTag(it, ite, "Artist:");
	params.artist_u_		=				   matchTag(it, ite, "ArtistUnicode:");
	params.creator_			=				   matchTag(it, ite, "Creator:");
	params.version_			=				   matchTag(it, ite, "Version:");
	params.source_			=				   matchTag(it, ite, "Source:");
	params.tags_			=	   processTags(matchTag(it, ite, "Tags:"));
	params.beatmap_id_		=		 std::stoi(matchTag(it, ite, "BeatmapID:"));
	params.beatmap_set_id_	=		 std::stoi(matchTag(it, ite, "BeatmapSetID:"));
	params.hp_				=		 std::stoi(matchTag(it, ite, "HPDrainRate:"));
	params.keys_			=		 std::stoi(matchTag(it, ite, "CircleSize:"));

	// TODO: Parse the hit objects and timing points	
	matchTag(it, ite, "[TimingPoints]"); // Move it to [TimingPoints]
	auto it_tp = it;
	matchTag(it, ite, "[HitObjects]"); // Move it to [TimingPoints]
	auto it_ho = it;

	readEO(getBetween(++it_tp, it_ho));
	readHO(getBetween(++it_ho, ite));
}

void VsrgMapOsu::saveFile(const std::string & file_path, bool overwrite) {
	
}

YAML::Node VsrgMapOsu::asYaml() const {
	auto node = VsrgMap::asYaml();
	node["params"] = params.asYaml();
	return node;
}

void VsrgMapOsu::readHO(const std::vector<std::string>& str_v) {
	for (const std::string & str : str_v) {
		SPtrTimedObject sptr = nullptr;
		if (isNormalNoteOsu(str)) {
			auto nn = NormalNoteOsu(str, params.keys_);
			sptr = std::make_shared<NormalNoteOsu>(nn);
		}
		else {
			auto ln = LongNoteOsu(str, params.keys_);
			sptr = std::make_shared<LongNoteOsu>(ln);
		}
		ho_v_->push_back(sptr);
	}
}

void VsrgMapOsu::readEO(const std::vector<std::string>& str_v) {
	for (const std::string & str : str_v) {
		SPtrTimedObject sptr = nullptr;
		if (isTimingPointOsu(str)) {
			auto tp = TimingPointOsu(str);
			sptr = std::make_shared<TimingPointOsu>(tp);
		}
		else {
			auto sp = ScrollPointOsu(str);
			sptr = std::make_shared<ScrollPointOsu>(sp);
		}
		eo_v_->push_back(sptr);
	}
}

bool VsrgMapOsu::isNormalNoteOsu(const std::string & str) {
	return std::count(str.begin(), str.end(), ':') == 4;
}

bool VsrgMapOsu::isTimingPointOsu(const std::string & str) {
	return str[str.length() - 3] == '1';
}


std::vector<unsigned int> VsrgMapOsu::processBookmarks(const std::string & str) {
	std::vector<std::string> uncasted = {};
	boost::split(uncasted, str, boost::is_any_of(","));
	std::vector<unsigned int> out = {};
	for (auto _ : uncasted) {
		out.push_back(std::stoi(_));
	}
	return std::move(out);
}

std::vector<std::string> VsrgMapOsu::processTags(const std::string & str) {
	std::vector<std::string> out = {};
	boost::split(out, str, boost::is_any_of(" "));
	return std::move(out);
}
