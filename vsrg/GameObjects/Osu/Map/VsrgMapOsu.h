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

	std::string processBackground(const std::string& str);

	std::vector<unsigned int> processBookmarks(const std::string & str);
	std::vector<std::string> processTags(const std::string & str);

	// Gets the value left of the ':' op
	std::string iterToTag(
		std::vector<std::string>::const_iterator & begin,
		std::vector<std::string>::const_iterator end,
		const std::string& starts_with) {

		auto begin_input = begin;
		while (begin != end) {
			if (boost::algorithm::starts_with(*begin, starts_with)) return *begin;
		}

		begin = begin_input; // Condition was never true
		return "";
	}
	std::string iterExtract(const std::string& str) {

	}
};

