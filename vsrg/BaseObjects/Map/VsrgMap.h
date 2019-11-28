#pragma once
#include <vector>
#include "BaseObjects/Multiple/HitObjectVector.h"
#include "BaseObjects/Multiple/EventObjectVector.h"

class VsrgMap
{
public:
	VsrgMap();
	~VsrgMap();
	
	// Load in derived format
	virtual void loadFile(const std::string & file_path) = 0;
	// Save in derived format
	virtual void saveFile(const std::string & file_path, bool overwrite) = 0;

protected:
	/// This writes all lines to the file from vector
	/// These have additional assertions for error handling
	virtual void writeFile(const std::vector<std::string> file_contents,
		const std::string & file_path, bool overwrite = false) final;

	/// This reads all lines from the file and coerces to vector.
	/// These have additional assertions for error handling
	virtual std::vector<std::string> readFile(const std::string & file_path);

};

