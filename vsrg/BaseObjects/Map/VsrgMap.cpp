#include "stdafx.h" 
#include "VsrgMap.h"
#include <iostream>

VsrgMap::VsrgMap() {}
VsrgMap::~VsrgMap() {}

void VsrgMap::saveAsYaml(const std::string & file_path, bool overwrite)
{
	if (!overwrite) {
		BOOST_ASSERT_MSG(!std::filesystem::exists(file_path),
			"File already exists.");
	}

	std::ofstream file_out(file_path);
	BOOST_ASSERT_MSG(file_out.is_open(), "File failed to open.");
	YAML::Node node = asYaml();
	file_out << node;

	file_out.close();
	BOOST_ASSERT_MSG(!file_out.is_open(), "File failed to close.");
}

void VsrgMap::readAsYaml(const std::string & file_path) {
	fromYaml(YAML::LoadFile(file_path));
}

YAML::Node VsrgMap::asYaml() const {
	YAML::Node node;
	node["hit_objects"] = ho_v_->asYaml();
	node["event_objects"] = eo_v_->asYaml();
	return node;
}

void VsrgMap::fromYaml(const YAML::Node & node) {
	ho_v_->fromYaml(node["hit_objects"]);
	eo_v_->fromYaml(node["event_objects"]);
}

std::vector<std::string> VsrgMap::readFile(const std::string & file_path) {
	std::ifstream file_stream;
	BOOST_ASSERT_MSG(std::filesystem::exists(file_path), "File doesn't exist.");

	std::vector<std::string> file_vector;
	std::string line = "";
	file_stream.open(file_path);
	while (std::getline(file_stream, line)) file_vector.push_back(line);

	file_stream.close();

	return std::move(file_vector);
}

void VsrgMap::writeFile(const std::vector<std::string> file_contents, const std::string & file_path, bool overwrite) {
	if (!overwrite) {
		BOOST_ASSERT_MSG(!std::filesystem::exists(file_path),
			"File already exists.");
	}

	std::ofstream file_out(file_path);
	BOOST_ASSERT_MSG(file_out.is_open(), "File failed to open.");
	for (const std::string & line : file_contents) {
		file_out << line << '\n';
	}

	file_out.close();
	BOOST_ASSERT_MSG(!file_out.is_open(), "File failed to close.");
}

SPtrHitObjectVector VsrgMap::getHitObjectVector() const {
	return ho_v_;
}

SPtrEventObjectVector VsrgMap::getEventObjectVector() const {
	return eo_v_;
}

void VsrgMap::setHitObjectVector(const SPtrHitObjectVector & ho_v) {
	ho_v_ = ho_v;
}

void VsrgMap::setEventObjectVector(const SPtrEventObjectVector & eo_v) {
	eo_v_ = eo_v;
}
