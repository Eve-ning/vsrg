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
	// Save in standard YAML format, depends on asYaml
	virtual void saveAsYaml(const std::string & file_path, bool overwrite) final;
	virtual void readAsYaml(const std::string & file_path) final {
		std::vector<std::string> lines = readFile(file_path);
	}

	// This is the universal default exporting function, it should be overridden to
	// add more nodes by derived classes
	virtual YAML::Node asYaml() const;
	virtual void fromYaml(const YAML::Node & node) {

		for (std::size_t i = 0; i < node.size(); i++) {

		}
	}

	virtual HitObjectVector getHitObjectVector() const final;
	virtual EventObjectVector getEventObjectVector() const final;
	virtual void setHitObjectVector(const HitObjectVector & ho_v) final;
	virtual void setEventObjectVector(const EventObjectVector & eo_v) final;

protected:
	/// This writes all lines to the file from vector
	/// These have additional assertions for error handling
	virtual void writeFile(const std::vector<std::string> file_contents,
		const std::string & file_path, bool overwrite = false) final;

	/// This reads all lines from the file and coerces to vector.
	/// These have additional assertions for error handling
	virtual std::vector<std::string> readFile(const std::string & file_path);

	HitObjectVector ho_v_;
	EventObjectVector eo_v_;
};

