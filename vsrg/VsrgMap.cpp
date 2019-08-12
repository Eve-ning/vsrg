#include "stdafx.h"
#include "VsrgMap.h"
#include <iostream>
#include <fstream>
#include <filesystem>

std::string VsrgMap::ho_v_tag_ = "// Hit Objects";
std::string VsrgMap::eo_v_tag_ = "// Event Objects";

VsrgMap::VsrgMap() {}
VsrgMap::~VsrgMap() {}

void VsrgMap::saveAsVsrg(const std::string & file_path, bool overwrite) {
	if (!overwrite) {
		BOOST_ASSERT_MSG(!std::filesystem::exists(file_path),
						 "File already exists.");
	}

	std::ofstream file_out;
	file_out.open(file_path, std::ios::in);
	BOOST_ASSERT_MSG(file_out.is_open(), "File failed to open.");
	file_out << ho_v_tag_;
	for (const std::string & ho_str : ho_v_.toExport()) {
		file_out << ho_str;
	}
	file_out << eo_v_tag_;
	for (const std::string & eo_str : eo_v_.toExport()) {
		file_out << eo_str;
	}

	file_out.close();
	BOOST_ASSERT_MSG(!file_out.is_open(), "File failed to close.");
}
