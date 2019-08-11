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
	virtual void saveFileVSRG(const std::string & file_path) = 0;

private:
	HitObjectVector ho_v_;
	EventObjectVector to_v_;
	
};

