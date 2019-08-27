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
	if (set_wide) setWideTitle(utf8ToUtf16(title));
}
std::string VsrgMapParams::getTitle() {
	return title_;
}
void VsrgMapParams::setArtist(const std::string & artist, bool set_wide = false) {
	artist_ = artist;
	if (set_wide) setWideArtist(utf8ToUtf16(artist));
}
std::string VsrgMapParams::getArtist() {
	return artist_;
}
void VsrgMapParams::setCreator(const std::string & creator, bool set_wide) {
	creator_ = creator;
	if (set_wide) setWideCreator(utf8ToUtf16(creator));
}
std::string VsrgMapParams::getCreator() {
	return creator_;
}
void VsrgMapParams::setVersion(const std::string & version, bool set_wide) {
	version_ = version;
	if (set_wide) setWideVersion(utf8ToUtf16(version));
}
std::string VsrgMapParams::getVersion() {
	return version_;
}
void VsrgMapParams::setWideCreator(const std::wstring & creator_w) {
	creator_w_ = creator_w;
}
std::wstring VsrgMapParams::getWideCreator() {
	return creator_w_;
}
void VsrgMapParams::setWideVersion(const std::wstring & version_w) {
	version_w_ = version_w;
}
std::wstring VsrgMapParams::getWideVersion() {
	return version_w_;
}
void VsrgMapParams::setWideTitle(const std::wstring & title_w) {
	title_w_ = title_w;
}
std::wstring VsrgMapParams::getWideTitle() {
	return title_w_;
}
void VsrgMapParams::setWideArtist(const std::wstring & artist_w) {
	artist_w_ = artist_w;
}
std::wstring VsrgMapParams::getWideArtist() {
	return artist_w_;
}

std::wstring VsrgMapParams::utf8ToUtf16(const std::string & utf8Str)
{
	// https://codereview.stackexchange.com/a/146738
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
	return conv.from_bytes(utf8Str);
}

std::string VsrgMapParams::utf16ToUtf8(const std::wstring & utf16Str)
{
	// https://codereview.stackexchange.com/a/146738
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
	return conv.to_bytes(utf16Str);
}
