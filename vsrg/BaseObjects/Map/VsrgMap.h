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
	virtual void saveAsYaml(const std::string & file_path, bool overwrite);

	// This is the universal default exporting function, it should be overridden to
	// add more nodes by derived classes
	virtual YAML::Node asYaml() const;

	virtual HitObjectVector getHitObjectVector() const final;
	virtual EventObjectVector getEventObjectVector() const final;
	virtual void setHitObjectVector(const HitObjectVector & ho_v) final;
	virtual void setEventObjectVector(const EventObjectVector & eo_v) final;

protected:
	/// This writes all lines to the file from vector
	/// These have additional assertions for error handling
	virtual void writeFile(const std::vector<std::string> file_contents,
		const std::string & file_path, bool overwrite = false) final;

	virtual void writeFile(const YAML::Node & node,
		const std::string & file_path, bool overwrite = false) final;

	/// This reads all lines from the file and coerces to vector.
	/// These have additional assertions for error handling
	virtual std::vector<std::string> readFile(const std::string & file_path);

	HitObjectVector ho_v_;
	EventObjectVector eo_v_;
};

