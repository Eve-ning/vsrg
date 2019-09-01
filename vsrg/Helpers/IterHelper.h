#pragma once
namespace IterHelper
{
	// Matches a string by starts_with and returns the content excluding starts_with
	std::string matchTag(
		std::vector<std::string>::const_iterator & begin,
		std::vector<std::string>::const_iterator end,
		const std::string & starts_with);

	// Grabs all strings in between begin and end (excluding end) and puts it into a vector
	std::vector<std::string> getBetween(
		std::vector<std::string>::const_iterator begin,
		std::vector<std::string>::const_iterator end
	);

	boost::tokenizer<boost::char_separator<char>> tokenize(
		const std::string & str, const char * separators);
};

