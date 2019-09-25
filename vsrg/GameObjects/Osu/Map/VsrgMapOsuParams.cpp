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
	hp_(hp), od_(od), keys_(keys), beatmap_id_(0), beatmap_set_id_(-1), preview_time_(0) {}

VsrgMapOsuParams::~VsrgMapOsuParams(){}
