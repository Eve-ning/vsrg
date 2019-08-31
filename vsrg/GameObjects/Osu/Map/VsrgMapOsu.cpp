#include "stdafx.h"
#include "VsrgMapOsu.h"
#include "Helpers/IterHelper.h"

VsrgMapOsu::VsrgMapOsu()
{
}

VsrgMapOsu::~VsrgMapOsu()
{
}

void VsrgMapOsu::loadFile(const std::string & file_path) {
	using namespace IterHelper;

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
	auto it_tp = it++;
	matchTag(it, ite, "[HitObjects]"); // Move it to [TimingPoints]
	auto it_ho = it++;

	params.bg_file_name_ = std::to_string(std::distance(it_tp, it_ho));
}

void VsrgMapOsu::saveFile(const std::string & file_path, bool overwrite) {
	// TODO:
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
	boost::split(out, str, boost::is_any_of(","));
	return std::move(out);
}
