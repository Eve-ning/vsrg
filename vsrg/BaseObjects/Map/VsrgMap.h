#pragma once
#include <vector>
#include "BaseObjects/Multiple/HitObjectVector.h"
#include "BaseObjects/Multiple/EventObjectVector.h"

class VsrgMap
{
public:
	VsrgMap();
	~VsrgMap();
	
	virtual void loadFile(const std::string & file_path) = 0;
	virtual void saveFile(const std::string & file_path, bool overwrite) = 0;

	// This is the universal exporting function
	virtual void saveAsVsrg(const std::string & file_path,
						    bool overwrite = false) final;

	/// This reads all lines from the file and coerces to vector.
	/// These have additional assertions for error handling
	virtual std::vector<std::string> readFile(const std::string & file_path);
	/// This writes all lines to the file from vector
	/// These have additional assertions for error handling
	virtual void writeFile(const std::vector<std::string> file_contents,
		const std::string & file_path, bool overwrite = false);

	static std::string ho_v_tag_;
	static std::string eo_v_tag_;

	virtual HitObjectVector getHitObjectVector() const final;
	virtual EventObjectVector getEventObjectVector() const final;
	virtual void setHitObjectVector(const HitObjectVector & ho_v) final;
	virtual void setEventObjectVector(const EventObjectVector & eo_v) final;

protected:
	HitObjectVector ho_v_;
	EventObjectVector eo_v_;
};

