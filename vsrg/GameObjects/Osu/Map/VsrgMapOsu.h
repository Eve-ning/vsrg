#pragma once
#include "BaseObjects/Map/VsrgMap.h"
#include "VsrgMapOsuParams.h"
#include "BaseObjects/Singular/Hit/HitObject.h"
#include "BaseObjects/Singular/Event/EventObject.h"
#include "GameObjects/Osu/Singular/Hit/NormalNoteOsu.h"
#include "GameObjects/Osu/Singular/Hit/LongNoteOsu.h"
#include "GameObjects/Osu/Singular/Event/ScrollPointOsu.h"
#include "GameObjects/Osu/Singular/Event/TimingPointOsu.h"
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

