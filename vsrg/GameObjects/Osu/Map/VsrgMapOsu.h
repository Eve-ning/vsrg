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

	void readHO(const std::vector<std::string> & str_v);
	void readEO(const std::vector<std::string> & str_v);

	bool isNormalNoteOsu(const std::string & str);
	bool isTimingPointOsu(const std::string & str);

	std::vector<unsigned int> processBookmarks(const std::string & str);
	std::vector<std::string> processTags(const std::string & str);

	// Inherited
	// void saveAsVsrg(const std::string & file_path, bool overwrite = false);
};

