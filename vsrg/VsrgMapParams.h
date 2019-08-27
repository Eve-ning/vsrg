#pragma once

/**
 * @brief Defines parameters for VsrgMap deriviations
 * 
 * All members are public, there are still helper functions for easier
 * setting of wstring and string at the same time for simplicity.
 */
class VsrgMapParams
{
public:
	VsrgMapParams();

	/// Custom wide string setting, use other constructor for lazy
	VsrgMapParams(
		const std::string & title, const std::string & artist,
		const std::string & creator, const std::string & version,
		const std::wstring & title_w, const std::wstring & artist_w,
		const std::wstring & creator_w, const std::wstring & version_w);

	/// Lazy wide string setting, they are copied from non-wide if set_wide == true
	VsrgMapParams(
		const std::string & title, const std::string & artist,
		const std::string & creator, const std::string & version,
		bool set_wide = true);

	~VsrgMapParams();

	virtual void setTitle(const std::string & title, bool set_wide = false) final;
	virtual void setArtist(const std::string & artist, bool set_wide = false) final;
	virtual void setCreator(const std::string & creator, bool set_wide = false) final;
	virtual void setVersion(const std::string & version, bool set_wide = false) final;
	virtual void setAudioFileName(const std::string & audio_file_name) final;

	/// Converts string to wstring
	static std::wstring toWStr(const std::string& utf8Str);
	/// Converts wstring to string
	static std::string toStr(const std::wstring& utf16Str);

	std::wstring audio_file_name_;
	std::wstring title_w_;
	std::string title_;
	std::wstring artist_w_;
	std::string artist_;
	std::wstring creator_w_;
	std::string creator_;
	std::wstring version_w_;
	std::string version_;
};

