#pragma once
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
	virtual std::string getTitle() final;
	virtual void setArtist(const std::string & artist, bool set_wide = false) final;
	virtual std::string getArtist();
	virtual void setCreator(const std::string & creator, bool set_wide = false) final;
	virtual std::string getCreator();
	virtual void setVersion(const std::string & version, bool set_wide = false) final;
	virtual std::string getVersion();
	virtual void setAudioFileName(const std::wstring & audio_file_name) final;
	virtual void setAudioFileName(const std::string & audio_file_name) final;
	virtual std::wstring getAudioFileName() const final;

	virtual void setWideCreator(const std::wstring & creator_w) final;
	virtual std::wstring getWideCreator() final;
	virtual void setWideVersion(const std::wstring & version_w) final;
	virtual std::wstring getWideVersion() final;
	virtual void setWideTitle(const std::wstring & title_w) final;
	virtual std::wstring getWideTitle() final;
	virtual void setWideArtist(const std::wstring & artist_w) final;
	virtual std::wstring getWideArtist() final;

	/// Converts string to wstring
	static std::wstring utf8ToUtf16(const std::string& utf8Str);
	/// Converts wstring to string
	static std::string utf16ToUtf8(const std::wstring& utf16Str);

private:
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

