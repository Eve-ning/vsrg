#include "stdafx.h"
#include "VsrgMapParams.h"

VsrgMapParams::VsrgMapParams() {}

VsrgMapParams::VsrgMapParams(const std::string & title, const std::string & artist, const std::string & creator, const std::string & version, const std::string & title_u, const std::string & artist_u, const std::string & creator_u, const std::string & version_u) :
	title_(title), artist_(artist), creator_(creator), version_(version),
	title_u_(title_u), artist_u_(artist_u), creator_u_(creator_u), version_u_(version_u) {}

VsrgMapParams::VsrgMapParams(const std::string & title, const std::string & artist, const std::string & creator, const std::string & version, bool set_unicode) {
	setTitle(title, set_unicode);
	setArtist(artist, set_unicode);
	setCreator(creator, set_unicode);
	setVersion(version, set_unicode);
}

VsrgMapParams::~VsrgMapParams() {}

void VsrgMapParams::setTitle(const std::string & title, bool set_unicode) {
	title_ = title;
	if (set_unicode) title_u_ = title;
}
void VsrgMapParams::setArtist(const std::string & artist, bool set_unicode) {
	artist_ = artist;
	if (set_unicode) artist_u_ = artist;
}
void VsrgMapParams::setCreator(const std::string & creator, bool set_unicode) {
	creator_ = creator;
	if (set_unicode) creator_u_ = creator;
}
void VsrgMapParams::setVersion(const std::string & version, bool set_unicode) {
	version_ = version;
	if (set_unicode) version_u_ = version;
}

void VsrgMapParams::setAudioFileName(const std::string & audio_file_name) {
	audio_file_name_ = audio_file_name;
}

YAML::Node VsrgMapParams::asYaml() const {
	YAML::Node node;
	node["audio_file_name"] = audio_file_name_;
	node["title_u"] = title_u_;
	node["title"] = title_;
	node["artist_u"] = artist_u_;
	node["artist"] = artist_;
	node["creator_u"] = creator_u_;
	node["creator"] = creator_;
	node["version_u"] = version_u_;
	node["version"] = version_;
	return std::move(node);
}

void VsrgMapParams::fromYaml(const YAML::Node & node) {
	audio_file_name_ = node["audio_file_name"].as<std::string>();
	title_u_ = node["title_u"].as<std::string>();
	title_ = node["title"].as<std::string>();
	artist_u_ = node["artist_u"].as<std::string>();
	artist_ = node["artist"].as<std::string>();
	creator_u_ = node["creator_u"].as<std::string>();
	creator_ = node["creator"].as<std::string>();
	version_u_ = node["version_u"].as<std::string>();
	version_ = node["version"].as<std::string>();
}
