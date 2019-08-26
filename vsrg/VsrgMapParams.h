#pragma once
class VsrgMapParams
{
public:
	/// This variant requires all to be filled, use the other for lazy instantiating
	VsrgMapParams(const std::string & title, const std::string & artist,
		const std::wstring & title_w, const std::wstring & artist_w);

	/// This variant allows lazy wide string setting and or just leaving wide variants blank
	VsrgMapParams(const std::string & title, const std::string & artist,
		bool set_wide = true);

	~VsrgMapParams();

	void setTitle(const std::string & title, bool set_wide = false);
	std::string getTitle();
	void setArtist(const std::string & artist, bool set_wide = false);
	std::string getArtist();
	/// Wide Variant is for unicode storage
	void setWideTitle(const std::wstring & title_w);
	/// Wide Variant is for unicode storage
	std::wstring getWideTitle();
	/// Wide Variant is for unicode storage
	void setWideArtist(const std::wstring & artist_w);
	/// Wide Variant is for unicode storage
	std::wstring getWideArtist();

	/// Converts string to wstring
	std::wstring utf8ToUtf16(const std::string& utf8Str);
	/// Converts wstring to string
	std::string utf16ToUtf8(const std::wstring& utf16Str);

private:
	std::wstring title_w_;
	std::string title_;
	std::wstring artist_w_;
	std::string artist_;
};

