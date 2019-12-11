#pragma once
#include "BaseObjects/Map/VsrgMap.h"
#include "GameObjects/SM/Map/VsrgMapSMParams.h"
#include "Helpers/MiscHelper.h"
#include "BaseObjects/Special/TimingGridBase.h"
#include <unordered_map>
class VsrgMapSM : public VsrgMap
{	
public:
	VsrgMapSM();
	~VsrgMapSM();

	virtual void loadFile(const std::string& file_path) override;
	virtual void saveFile(const std::string& file_path, bool overwrite = false) override;

	VsrgMapSMParams params;

	static const double SNAP_ERROR_MARGIN;
private:

	std::unordered_map<std::string, std::vector<std::string>> toUMap(
		std::vector<std::string>::const_iterator& begin,
		std::vector<std::string>::const_iterator end);

	TimingGridBase tgb;
};

