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
	std::vector<std::string> file_contents = readFile(file_path);

	// To convert to using boost::qi when im not lazy
	
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
	params.hp_				=		 std::stod(matchTag(it, ite, "HPDrainRate:"));
	params.keys_			=		 std::stoi(matchTag(it, ite, "CircleSize:"));
	params.od_				=		 std::stod(matchTag(it, ite, "OverallDifficulty:"));

	matchTag(it, ite, "[TimingPoints]"); // Move it to [TimingPoints]
	auto it_tp = it;
	matchTag(it, ite, "[HitObjects]"); // Move it to [TimingPoints]
	auto it_ho = it;

	readEO(getBetween(++it_tp, it_ho));
	readHO(getBetween(++it_ho, ite));
}

void VsrgMapOsu::saveFile(const std::string & file_path, bool overwrite) {
	std::vector<std::string> contents = {};
	auto _ = [&contents](const std::string & str) { contents.push_back(str); };

	_("osu file format v14");

	_("[General]");
	_("AudioFilename: " + params.audio_file_name_);
	_("AudioLeadIn : 0");
	_("PreviewTime : " + std::to_string(params.preview_time_));
	_("Countdown : 0");
	_("SampleSet : Soft");
	_("StackLeniency : 0.7");
	_("Mode : 3");
	_("LetterboxInBreaks : 0");
	_("SpecialStyle : 0");
	_("WidescreenStoryboard : 0");
	_("SamplesMatchPlaybackRate : 1");

	_("[Editor]");
	std::string bookmarks = "";
	for (const auto& bookmark : params.bookmarks_) bookmarks += "," + std::to_string(bookmark);
	_("Bookmarks: " + bookmarks.substr(1, std::string::npos));
	_("DistanceSpacing : 0.6");
	_("BeatDivisor : 4");
	_("GridSize : 32");
	_("TimelineZoom : 1.8");

	_("[Metadata]");
	_("Title : " + params.title_);
	_("TitleUnicode : " + params.title_u_);
	_("Artist : " + params.artist_);
	_("ArtistUnicode :" + params.artist_u_);
	_("Creator : " + params.creator_);
	_("Version : " + params.version_);
	_("Source :" + params.source_);
	std::string tags = "";
	for (const auto& tag : params.tags_) tags += " " + tag;
	_("Tags:" + tags);
	_("BeatmapID : " + std::to_string(params.beatmap_id_));
	_("BeatmapSetID : " + std::to_string(params.beatmap_set_id_));

	_("[Difficulty]");
	_("HPDrainRate : " + std::to_string(params.hp_));
	_("CircleSize : " + std::to_string(params.keys_));
	_("OverallDifficulty : " + std::to_string(params.od_));
	_("ApproachRate : 5");
	_("SliderMultiplier : 1");
	_("SliderTickRate : 1");

	_("[Events]");
	_("0, 0, " + params.bg_file_name_ + ", 0, 0");

	_("[TimingPoints]");
	for (const auto& eo : eo_v_->getEventObjectVector()) _(eo->asNative());

	_("[HitObjects]");
	for (const auto& ho : ho_v_->getHitObjectVector()) _(ho->asNative(params.keys_));
	
	writeFile(contents, file_path, overwrite);
}

YAML::Node VsrgMapOsu::asYaml() const {
	auto node = VsrgMap::asYaml();
	node["params"] = params.asYaml();
	return node;
}

void VsrgMapOsu::fromYaml(const YAML::Node & node) {
	eo_v_->fromYaml(node["hit_objects"]);
	ho_v_->fromYaml(node["event_objects"]);
	params.fromYaml(node["params"]);
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
