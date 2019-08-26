#include "stdafx.h"
#include "VsrgMapParams.h"


VsrgMapParams::VsrgMapParams()
{
}



/// This variant requires all to be filled, use the other for lazy instantiating

VsrgMapParams::VsrgMapParams(const std::string & title, const std::string & artist, const std::wstring & title_w, const std::wstring & artist_w) :
	title_(title), artist_(artist), title_w_(title_w), artist_w_(artist_w)
{
}


/// This variant allows lazy wide string setting and or just leaving wide variants blank

VsrgMapParams::VsrgMapParams(const std::string & title, const std::string & artist, bool set_wide) : title_w_(L""), artist_w_(L"")
{
	setTitle(title, set_wide);
	setArtist(artist, set_wide);
}

VsrgMapParams::~VsrgMapParams()
{
}

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
