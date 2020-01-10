#pragma once
#include "BaseObjects/Map/VsrgMapParams.h"
class VsrgMapSMParams : public VsrgMapParams
{
public:
	VsrgMapSMParams(
		const std::string & subtitle,
		const std::string & subtitle_u,
		const std::string & genre,
		const std::string & bn_path,
		const std::string & bg_path,
		const std::string & lyr_path,
		const std::string & cd_path,
		const double & offset,
		const double & preview_time_start,
		const double & preview_time_end,
		const std::string & display_bpm,
		const std::string & chart_type,
		const std::string & group,
		const std::string & difficulty_name,
		const std::string & difficulty_val,
		const VsrgMapParams & vsrg_map_params);

	VsrgMapSMParams(
		const std::string & subtitle,
		const std::string & subtitle_u,
		const std::string & genre,
		const std::string & bn_path,
		const std::string & bg_path,
		const std::string & lyr_path,
		const std::string & cd_path,
		const double & offset,
		const double & preview_time_start,
		const double & preview_time_end,
		const std::string & display_bpm,
		const std::string & chart_type,
		const std::string & group,
		const std::string & difficulty_name,
		const std::string & difficulty_val,
		const std::string & title, const std::string & artist,
		const std::string & creator, const std::string & version,
		const std::string & title_u, const std::string & artist_u,
		const std::string & creator_u, const std::string & version_u);

	VsrgMapSMParams();

	std::string subtitle_;
	std::string subtitle_u_;
	std::string genre_;
	std::string bn_path_;
	std::string bg_path_;
	std::string lyr_path_;
	std::string cd_path_;
	double offset_;
	double preview_time_start_;
	double preview_time_end_;
	std::string display_bpm_;
	std::string chart_type_;
	std::string group_;
	std::string difficulty_name_;
	std::string difficulty_val_;
};