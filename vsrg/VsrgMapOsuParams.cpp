#include "stdafx.h"
#include "VsrgMapOsuParams.h"

VsrgMapOsuParams::VsrgMapOsuParams() {}

VsrgMapOsuParams::VsrgMapOsuParams(
	double hp,
	double od,
	unsigned int preview_time,
	unsigned int keys,
	const std::wstring & bg_file_name,
	const std::wstring & source,
	const std::vector<std::wstring>& tags,
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
	const std::wstring & bg_file_name,
	const std::wstring & source,
	const std::vector<std::wstring>& tags,
	const std::vector<unsigned int>& bookmarks,
	int beatmap_id, int beatmap_set_id,
	const std::string & title,
	const std::string & artist,
	const std::string & creator,
	const std::string & version,
	const std::wstring & title_w,
	const std::wstring & artist_w,
	const std::wstring & creator_w,
	const std::wstring & version_w) :
	VsrgMapParams(title, artist, creator, version, title_w, artist_w, creator_w, version_w),
	hp_(hp), od_(od), preview_time_(preview_time), keys_(keys),
	bg_file_name_(bg_file_name), source_(source), tags_(tags),
	bookmarks_(bookmarks), beatmap_id_(beatmap_id), beatmap_set_id_(beatmap_set_id) {}

VsrgMapOsuParams::VsrgMapOsuParams(double hp, double od, unsigned int keys, const std::string & title, const std::string & artist, const std::string & creator, const std::string & version, bool set_wide) :
	VsrgMapParams(title, artist, creator, version, set_wide),
	hp_(hp), od_(od), keys_(keys) {}

VsrgMapOsuParams::~VsrgMapOsuParams()
{
}
