#include "stdafx.h"
#include "VsrgMapSMParams.h"

VsrgMapSMParams::VsrgMapSMParams(const std::string& subtitle, const std::string& genre, const std::string& bn_path, const std::string& bg_path, const std::string& lyr_path, const std::string& cd_path, const double& offset, const double& preview_time_start, const double& preview_time_end, const std::string& display_bpm, const std::string& chart_type, const std::string& difficulty_name, const double& difficulty_val, const VsrgMapParams& vsrg_map_params) :
	subtitle_(subtitle),
	genre_(genre),
	bn_path_(bn_path),
	bg_path_(bg_path),
	lyr_path_(lyr_path),
	cd_path_(cd_path),
	offset_(offset),
	preview_time_start_(preview_time_start),
	preview_time_end_(preview_time_end),
	display_bpm_(display_bpm),
	chart_type_(chart_type),
	difficulty_name_(difficulty_name),
	VsrgMapParams(vsrg_map_params) {}

VsrgMapSMParams::VsrgMapSMParams(const std::string& subtitle, const std::string& genre, const std::string& bn_path, const std::string& bg_path, const std::string& lyr_path, const std::string& cd_path, const double& offset, const double& preview_time_start, const double& preview_time_end, const std::string& display_bpm, const std::string& chart_type, const std::string& difficulty_name, const double& difficulty_val, const std::string& title, const std::string& artist, const std::string& creator, const std::string& version, const std::string& title_u, const std::string& artist_u, const std::string& creator_u, const std::string& version_u) :
	subtitle_(subtitle),
	genre_(genre),
	bn_path_(bn_path),
	bg_path_(bg_path),
	lyr_path_(lyr_path),
	cd_path_(cd_path),
	offset_(offset),
	preview_time_start_(preview_time_start),
	preview_time_end_(preview_time_end),
	display_bpm_(display_bpm),
	chart_type_(chart_type),
	difficulty_name_(difficulty_name),
	VsrgMapParams(title, artist, creator, version,
		title_u, artist_u, creator_u, version_u) {}
