#pragma once
#include "VsrgMap.h"
#include "VsrgMapOsuParams.h"
#include "HitObject.h"
class VsrgMapOsu :
	public VsrgMap
{
public:
	VsrgMapOsu();
	~VsrgMapOsu();

	virtual void loadFile(const std::string & file_path) override;
	virtual void saveFile(const std::string & file_path, bool overwrite = false) override;

	SPtrHitObject readHO(const std::string & str);
	SPtrEventObject readEO(const std::string & str);

private:

	/// This gets an inline tag, e.g. "AudioFileName: audio.mp3" gives "audio.mp3"
	std::string matchTag(
		std::vector<std::string>::const_iterator & begin,
		std::vector<std::string>::const_iterator end,
		const std::string & starts_with) const;

	std::vector<unsigned int> processBookmarks(const std::string & str);
	std::vector<std::string> processTags(const std::string & str);

	// Inherited
	// void saveAsVsrg(const std::string & file_path, bool overwrite = false);

	VsrgMapOsuParams params;
};

