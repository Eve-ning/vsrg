#include "stdafx.h"
#include "VsrgMap.h"
#include <iostream>


std::string VsrgMap::ho_v_tag_ = "// Hit Objects";
std::string VsrgMap::eo_v_tag_ = "// Event Objects";

VsrgMap::VsrgMap() {}
VsrgMap::~VsrgMap() {}

void VsrgMap::saveAsVsrg(const std::string & file_path, bool overwrite) {

	std::vector<std::string> file_contents = {};

	file_contents.push_back(ho_v_tag_);
	for (const std::string & ho_str : ho_v_.toExport()) {
		file_contents.push_back(ho_str);
	}
	file_contents.push_back(eo_v_tag_);
	for (const std::string & eo_str : eo_v_.toExport()) {
		file_contents.push_back(eo_str);
	}

	writeFile(std::move(file_contents), file_path, overwrite);
}

std::vector<std::string> VsrgMap::readFile(const std::string & file_path) {
	std::ifstream file_stream;
	BOOST_ASSERT_MSG(std::filesystem::exists(file_path), "File doesn't exist.");

	std::vector<std::string> file_vector;
	std::string line = "";
	file_stream.open(file_path);
	while (std::getline(file_stream, line)) {
		file_vector.push_back(line);
	}

	file_stream.close();

	return std::move(file_vector);
}

void VsrgMap::writeFile(const std::vector<std::string> file_contents, const std::string & file_path, bool overwrite) {
	if (!overwrite) {
		BOOST_ASSERT_MSG(!std::filesystem::exists(file_path),
			"File already exists.");
	}

	std::ofstream file_out;
	file_out.open(file_path, std::ios::in);
	BOOST_ASSERT_MSG(file_out.is_open(), "File failed to open.");
	for (const std::string & line : file_contents) {
		file_out << line << '\n';
	}

	file_out.close();
	BOOST_ASSERT_MSG(!file_out.is_open(), "File failed to close.");
}

HitObjectVector VsrgMap::getHitObjectVector() const {
	return ho_v_;
}

EventObjectVector VsrgMap::getEventObjectVector() const {
	return eo_v_;
}

void VsrgMap::setHitObjectVector(const HitObjectVector & ho_v) {
	ho_v_ = ho_v;
}

void VsrgMap::setEventObjectVector(const EventObjectVector & eo_v) {
	eo_v_ = eo_v;
}
