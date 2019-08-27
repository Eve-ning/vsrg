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

void VsrgMapParams::setTitle(const std::string & title, bool set_unicode = false) {
	title_ = title;
	if (set_unicode) title_u_ = toWStr(title);
}
void VsrgMapParams::setArtist(const std::string & artist, bool set_unicode = false) {
	artist_ = artist;
	if (set_unicode) artist_u_ = toWStr(artist);
}
void VsrgMapParams::setCreator(const std::string & creator, bool set_unicode) {
	creator_ = creator;
	if (set_unicode) creator_u_ = toWStr(creator);
}
void VsrgMapParams::setVersion(const std::string & version, bool set_unicode) {
	version_ = version;
	if (set_unicode) version_u_ = toWStr(version);
}

void VsrgMapParams::setAudioFileName(const std::string & audio_file_name) {
	audio_file_name_ = toWStr(audio_file_name);
}