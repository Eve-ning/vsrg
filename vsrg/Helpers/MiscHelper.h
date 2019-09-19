#pragma once

namespace IterHelper
{
	// Matches a string by starts_with and returns the content excluding starts_with
	// E.g. "Number: 3", starts_with = "Number: ", returns "3"
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
}

namespace StringHelper {
	static constexpr char formatDblf[] = "%.5f";
	// Converts double to string without scientific notation or trailing zeros
	std::string formatDbl(const double & val);
}

