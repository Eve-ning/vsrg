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
		const std::string & title_u, const std::string & artist_u,
		const std::string & creator_u, const std::string & version_u);

	/// Lazy wide string setting, they are copied from non-wide if set_unicode == true
	VsrgMapParams(
		const std::string & title, const std::string & artist,
		const std::string & creator, const std::string & version,
		bool set_unicode = true);

	~VsrgMapParams();

	virtual void setTitle(const std::string & title, bool set_unicode = false) final;
	virtual void setArtist(const std::string & artist, bool set_unicode = false) final;
	virtual void setCreator(const std::string & creator, bool set_unicode = false) final;
	virtual void setVersion(const std::string & version, bool set_unicode = false) final;
	virtual void setAudioFileName(const std::string & audio_file_name) final;

	std::string audio_file_name_;
	std::string title_u_;
	std::string title_;
	std::string artist_u_;
	std::string artist_;
	std::string creator_u_;
	std::string creator_;
	std::string version_u_;
	std::string version_;
};

