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

	static const double SNAP_ERROR_MARGIN;
private:

	struct Bpm {
		Bpm(double offset_, double bpm_) :
			offset(offset_), bpm(bpm_) {}
		double offset;
		double bpm;
	};
	struct Note {
		Note(double offset_, int index_, char chr_) :
			offset(offset_), index(index_), chr(chr_) {}
		double offset;
		int index;
		char chr;
	};

	void readHO(const std::vector<std::string> & ho_v,
		const SPtrEventObjectVector eo_v);

	std::vector<Bpm>
		 processBpms(const std::vector<std::string>::iterator & begin,
					 const std::vector<std::string>::iterator & end);
	void processStops(const std::vector<std::string>::iterator & begin,
					  const std::vector<std::string>::iterator & end);
	void processObjs(std::vector<std::string>::iterator begin,
				   const std::vector<std::string>::iterator & end,
				   const std::vector<Bpm> & bpm_pair_v,
				   double offset);
	void processHOBeat(std::vector<std::string>::iterator begin,
						const std::vector<std::string>::iterator & end,
						double offset,
						double step_size);

	std::unordered_map<std::string, std::vector<std::string>> toUMap(
		std::vector<std::string>::const_iterator& begin,
		std::vector<std::string>::const_iterator end);


};

