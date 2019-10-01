#pragma once

namespace IterHelper
{
	// Grabs all strings in between begin and end (excluding end) and puts it into a vector
	std::vector<std::string> getBetween(
		std::vector<std::string>::const_iterator begin,
		std::vector<std::string>::const_iterator end
	);

	std::vector<std::string> tokenize(
		const std::string & str, const char * separators,
		size_t pad_size = 0);
}

namespace StringHelper {
	static constexpr char formatDblf[] = "%.5f";
	// Converts double to string without scientific notation or trailing zeros
	std::string formatDbl(const double & val);
}

