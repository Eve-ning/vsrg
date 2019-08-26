#pragma once
class VsrgMapParams
{
public:
	/// This variant requires all to be filled, use the other for lazy instantiating
	VsrgMapParams(
		const std::string & title, const std::string & artist,
		const std::string & creator, const std::string & version,
		const std::wstring & title_w, const std::wstring & artist_w,
		const std::wstring & creator_w, const std::wstring & version_w) :
		title_(title), artist_(artist), creator_(creator), version_(version),
		title_w_(title_w), artist_w_(artist_w), creator_w_(creator_w), version_w_(version_w)
	{
	}

	/// This variant allows lazy wide string setting and or just leaving wide variants blank
	VsrgMapParams(
		const std::string & title, const std::string & artist,
		const std::string & creator, const std::string & version,
		bool set_wide = true) :
		title_w_(L""), artist_w_(L""), creator_w_(L""), version_w_(L"") {
		setTitle(title, set_wide);
		setArtist(artist, set_wide);
		setCreator(creator, set_wide);
		setVersion(version, set_wide);
	}

	~VsrgMapParams();

	void setTitle(const std::string & title, bool set_wide = false);
	std::string getTitle();
	void setArtist(const std::string & artist, bool set_wide = false);
	std::string getArtist();
	void setCreator(const std::string & creator, bool set_wide = false);
	std::string getCreator();
	void setVersion(const std::string & version, bool set_wide = false);
	std::string getVersion();


	void setWideCreator(const std::wstring & creator_w);
	std::wstring getWideCreator();
	void setWideVersion(const std::wstring & version_w);
	std::wstring getWideVersion();

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
	std::wstring creator_w_;
	std::string creator_;
	std::wstring version_w_;
	std::string version_;
};

