#include "stdafx.h"
#include "VsrgMapOsuParams.h"

VsrgMapOsuParams::VsrgMapOsuParams() {}

VsrgMapOsuParams::VsrgMapOsuParams(
	double hp,
	double od,
	unsigned int preview_time,
	unsigned int keys,
	const std::string & bg_file_name,
	const std::string & source,
	const std::vector<std::string>& tags,
	const std::vector<unsigned int>& bookmarks,
	int beatmap_id,
	int beatmap_set_id,
	VsrgMapParams vsrg_map_params) :
	VsrgMapParams(vsrg_map_params),
	hp_(hp), od_(od), preview_time_(preview_time), keys_(keys),
	bg_file_name_(bg_file_name), source_(source), tags_(tags),
	bookmarks_(bookmarks), beatmap_id_(beatmap_id), beatmap_set_id_(beatmap_set_id) {}

VsrgMapOsuParams::VsrgMapOsuParams(
	double hp, double od, unsigned int preview_time, unsigned int keys,
	const std::string & bg_file_name,
	const std::string & source,
	const std::vector<std::string>& tags,
	const std::vector<unsigned int>& bookmarks,
	int beatmap_id, int beatmap_set_id,
	const std::string & title,
	const std::string & artist,
	const std::string & creator,
	const std::string & version,
	const std::string & title_u,
	const std::string & artist_u,
	const std::string & creator_u,
	const std::string & version_u) :
	VsrgMapParams(title, artist, creator, version, title_u, artist_u, creator_u, version_u),
	hp_(hp), od_(od), preview_time_(preview_time), keys_(keys),
	bg_file_name_(bg_file_name), source_(source), tags_(tags),
	bookmarks_(bookmarks), beatmap_id_(beatmap_id), beatmap_set_id_(beatmap_set_id) {}

VsrgMapOsuParams::VsrgMapOsuParams(double hp, double od, unsigned int keys, const std::string & title, const std::string & artist, const std::string & creator, const std::string & version, bool set_unicode) :
	VsrgMapParams(title, artist, creator, version, set_unicode),
	hp_(hp), od_(od), keys_(keys) {}

VsrgMapOsuParams::~VsrgMapOsuParams(){}

YAML::Node VsrgMapOsuParams::asYaml() const {
	YAML::Node node = VsrgMapParams::asYaml();
	node["hp"] = hp_;
	node["od"] = od_;
	node["preview_time"] = preview_time_;
	node["keys"] = keys_;
	node["bg_file_name"] = bg_file_name_;
	node["source"] = source_;
	node["tags"] = tags_;
	node["bookmarks"] = bookmarks_;
	node["beatmap_id"] = beatmap_id_;
	node["beatmap_set_id"] = beatmap_set_id_;
	return std::move(node);
}

void VsrgMapOsuParams::fromYaml(const YAML::Node & node){
	VsrgMapParams::fromYaml(node);
	hp_	= node["hp"].as<double>();
	od_	= node["od"].as<double>();
	preview_time_ = node["preview_time"].as<unsigned int>();
	keys_ = node["keys"].as<unsigned int>();
	bg_file_name_ = node["bg_file_name"].as<std::string>();
	source_	= node["source"].as<std::string>();
	tags_ = node["tags"].as<std::vector<std::string>>();
	bookmarks_ = node["bookmarks"].as<std::vector<unsigned int>>();
	beatmap_id_	= node["beatmap_id"].as<int>();
	beatmap_set_id_	= node["beatmap_set_id"].as<int>();
}
