#pragma once
#include "BaseObjects/Map/VsrgMapParams.h"

/* Comments:
	
	Constructors
	I'll avoid any default arguments in this derived class since we are essentially
	reading off a pre-determined osu file

	Downcasting
	Safe downcasting is implemented in a constructor, other members just have to be
	specified

*/

class VsrgMapOsuParams : public VsrgMapParams
{
public:
	VsrgMapOsuParams();

	VsrgMapOsuParams(
		double hp, double od, unsigned int preview_time, unsigned int keys,
		const std::string & bg_file_name,
		const std::string & source,
		const std::vector<std::string> & tags,
		const std::vector<unsigned int> & bookmarks,
		int beatmap_id, int beatmap_set_id,
		VsrgMapParams vsrg_map_params);

	/// Custom unicode string setting, use other constructor for lazy
	VsrgMapOsuParams(
		double hp, double od, unsigned int preview_time, unsigned int keys,
		const std::string & bg_file_name,
		const std::string & source,
		const std::vector<std::string> & tags,
		const std::vector<unsigned int> & bookmarks,
		int beatmap_id, int beatmap_set_id,
		const std::string & title, const std::string & artist,
		const std::string & creator, const std::string & version,
		const std::string & title_u, const std::string & artist_u,
		const std::string & creator_u, const std::string & version_u);

	/// Lazy unicode string setting, they are copied from non-wide if set_unicode == true
	VsrgMapOsuParams(double hp, double od, unsigned int keys,
		const std::string & title, const std::string & artist,
		const std::string & creator, const std::string & version,
		bool set_unicode = true);

	~VsrgMapOsuParams();


	double hp_;
	double od_;
	unsigned int preview_time_;
	unsigned int keys_;
	std::string bg_file_name_;
	std::string source_;
	std::vector<std::string> tags_;
	std::vector<unsigned int> bookmarks_;
	int beatmap_id_;
	int beatmap_set_id_;
};

