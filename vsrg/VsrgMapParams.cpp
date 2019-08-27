#include "stdafx.h"
#include "VsrgMapParams.h"

VsrgMapParams::VsrgMapParams() {}

VsrgMapParams::VsrgMapParams(const std::string & title, const std::string & artist, const std::string & creator, const std::string & version, const std::wstring & title_w, const std::wstring & artist_w, const std::wstring & creator_w, const std::wstring & version_w) :
	title_(title), artist_(artist), creator_(creator), version_(version),
	title_w_(title_w), artist_w_(artist_w), creator_w_(creator_w), version_w_(version_w) {}

VsrgMapParams::VsrgMapParams(const std::string & title, const std::string & artist, const std::string & creator, const std::string & version, bool set_wide) {
	setTitle(title, set_wide);
	setArtist(artist, set_wide);
	setCreator(creator, set_wide);
	setVersion(version, set_wide);
}

VsrgMapParams::~VsrgMapParams() {}

void VsrgMapParams::setTitle(const std::string & title, bool set_wide = false) {
	title_ = title;
	if (set_wide) title_w_ = toWStr(title);
}
void VsrgMapParams::setArtist(const std::string & artist, bool set_wide = false) {
	artist_ = artist;
	if (set_wide) artist_w_ = toWStr(artist);
}
void VsrgMapParams::setCreator(const std::string & creator, bool set_wide) {
	creator_ = creator;
	if (set_wide) creator_w_ = toWStr(creator);
}
void VsrgMapParams::setVersion(const std::string & version, bool set_wide) {
	version_ = version;
	if (set_wide) version_w_ = toWStr(version);
}

void VsrgMapParams::setAudioFileName(const std::string & audio_file_name) {
	audio_file_name_ = toWStr(audio_file_name);
}
std::wstring VsrgMapParams::toWStr(const std::string & utf8Str)
{
	// https://codereview.stackexchange.com/a/146738
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
	return conv.from_bytes(utf8Str);
}

std::string VsrgMapParams::toStr(const std::wstring & utf16Str)
{
	// https://codereview.stackexchange.com/a/146738
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
	return conv.to_bytes(utf16Str);
}
