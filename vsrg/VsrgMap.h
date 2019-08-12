#pragma once
#include <vector>
#include "HitObjectVector.h"
#include "EventObjectVector.h"

class VsrgMap
{
public:
	VsrgMap();
	~VsrgMap();
	
	virtual void loadFile(const std::string & file_path) = 0;
	virtual void saveFile(const std::string & file_path) = 0;

	// This is the universal exporting function
	virtual void saveAsVsrg(const std::string & file_path, bool overwrite = false);

	static std::string ho_v_tag_;
	static std::string eo_v_tag_;

private:
	HitObjectVector ho_v_;
	EventObjectVector eo_v_;
};

