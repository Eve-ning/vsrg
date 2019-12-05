	#pragma once
#include "BaseObjects/Map/VsrgMap.h"
#include "VsrgMapOsuParams.h"

class VsrgMapOsu :
	public VsrgMap
{
public:
	VsrgMapOsu();
	~VsrgMapOsu();

	virtual void loadFile(const std::string & file_path) override;
	virtual void saveFile(const std::string & file_path, bool overwrite = false) override;

	VsrgMapOsuParams params;

private:

	bool isNormalNoteOsu(const std::string & str);
	bool isTimingPointOsu(const std::string & str);

	std::string processBackground(const std::string& str);
	std::vector<unsigned int> processBookmarks(const std::string & str);
	std::vector<std::string> processTags(const std::string & str);
	void processHO(const std::vector<std::string> & str_v);
	void processEO(const std::vector<std::string> & str_v);

	// Gets the value left of the ':' op
	std::string iterToTag(
		std::vector<std::string>::const_iterator & begin,
		std::vector<std::string>::const_iterator end,
		const std::string& starts_with);
};

