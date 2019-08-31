#pragma once
#include "BaseObjects/Map/VsrgMap.h"
#include "VsrgMapOsuParams.h"
#include "BaseObjects/Singular/Hit/HitObject.h"
#include "BaseObjects/Singular/Event/EventObject.h"
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

	VsrgMapOsuParams params;

private:

	std::vector<unsigned int> processBookmarks(const std::string & str);
	std::vector<std::string> processTags(const std::string & str);

	// Inherited
	// void saveAsVsrg(const std::string & file_path, bool overwrite = false);
};

