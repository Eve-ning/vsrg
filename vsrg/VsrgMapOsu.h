#pragma once
#include "VsrgMap.h"
class VsrgMapOsu :
	public VsrgMap
{
public:
	VsrgMapOsu();
	~VsrgMapOsu();

	virtual void loadFile(const std::string & file_path) override;
	virtual void saveFile(const std::string & file_path, bool overwrite = false) override;

	// Inherited
	// void saveAsVsrg(const std::string & file_path, bool overwrite = false);
};

