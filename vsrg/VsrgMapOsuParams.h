#pragma once
#include "VsrgMapParams.h"

/* Comments:
	
	Constructors
	I'll avoid any default arguments in this derived class since we are essentially
	reading off a pre-determined osu file

	Downcasting
	Safe downcasting is implemented in a constructor, other members just have to be
	specified

*/

class VsrgMapOsuParams : VsrgMapParams
{
public:
	VsrgMapOsuParams();

	VsrgMapOsuParams(
		double hp, double od, unsigned int preview_time, unsigned int keys,
		const std::wstring & bg_file_name,
		const std::wstring & source,
		const std::vector<std::wstring> & tags,
		const std::vector<unsigned int> & bookmarks,
		int beatmap_id, int beatmap_set_id,
		VsrgMapParams vsrg_map_params);

	/// Custom wide string setting, use other constructor for lazy
	VsrgMapOsuParams(
		double hp, double od, unsigned int preview_time, unsigned int keys,
		const std::wstring & bg_file_name,
		const std::wstring & source,
		const std::vector<std::wstring> & tags,
		const std::vector<unsigned int> & bookmarks,
		int beatmap_id, int beatmap_set_id,
		const std::string & title, const std::string & artist,
		const std::string & creator, const std::string & version,
		const std::wstring & title_w, const std::wstring & artist_w,
		const std::wstring & creator_w, const std::wstring & version_w);

	/// Lazy wide string setting, they are copied from non-wide if set_wide == true
	VsrgMapOsuParams(double hp, double od, unsigned int keys,
		const std::string & title, const std::string & artist,
		const std::string & creator, const std::string & version,
		bool set_wide = true);

	~VsrgMapOsuParams();

	double hp_;
	double od_;
	unsigned int preview_time_;
	unsigned int keys_;
	std::wstring bg_file_name_;
	std::wstring source_;
	std::vector<std::wstring> tags_;
	std::vector<unsigned int> bookmarks_;
	int beatmap_id_;
	int beatmap_set_id_;
};

