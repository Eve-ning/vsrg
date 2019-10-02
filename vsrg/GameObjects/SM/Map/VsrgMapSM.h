#pragma once
#include "BaseObjects/Map/VsrgMap.h"
#include "GameObjects/SM/Map/VsrgMapSMParams.h"
#include "Helpers/MiscHelper.h"
#include <unordered_map>
class VsrgMapSM : public VsrgMap
{	
public:
	VsrgMapSM();
	~VsrgMapSM();

	virtual void loadFile(const std::string& file_path) override;
	virtual void saveFile(const std::string& file_path, bool overwrite = false) override;

	VsrgMapSMParams params;
private:

	void readHO(const std::vector<std::string> & ho_v,
		const SPtrEventObjectVector eo_v);

	void readHOChunk(const std::vector<std::string>& str_v);

	void processBpms(const std::vector<std::string>& str_v, double offset);
	void processStops(const std::vector<std::string>& str_v, SPtrEventObjectVector eo_v);

	std::unordered_map<std::string, std::vector<std::string>> toUMap(
		std::vector<std::string>::const_iterator& begin,
		std::vector<std::string>::const_iterator end);
};

