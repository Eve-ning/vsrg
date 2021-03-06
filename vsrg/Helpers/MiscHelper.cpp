#include "stdafx.h"
#include "MiscHelper.h"
#include <sstream>

std::string IterHelper::matchTag(std::vector<std::string>::const_iterator & begin,
	std::vector<std::string>::const_iterator end, const std::string & starts_with) {
	std::string str = "";
	auto begin_input = begin;
	while (begin != end) {
		str = *begin;
		if (boost::algorithm::starts_with(str, starts_with)) {
			// substr doesn't break on out of range index, it just returns nothing
			str = str.substr(starts_with.length());
			boost::trim(str);
			return str;
		}
		begin++;
	}
	// We will revert the begin to the input iter if the tag is totally missing
	if (begin == end) {
		begin = begin_input;
	}
	// Don't need to assert, just return nothing
	//BOOST_ASSERT_MSG(false, "Failed to match Tag"); 
	return str;
}

std::vector<std::string> IterHelper::getBetween(std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end) {
	std::vector<std::string> out;
	while (begin != end) {
		auto _ = *begin; begin++;
		if (_.length() == 0) continue;
		out.push_back(_);
	}
	return std::move(out);
}

std::vector<std::string> IterHelper::tokenize(const std::string & str, const char * separators,
	size_t pad_size) {
	std::vector<std::string> tokens;

	size_t cur = 0;
	size_t prev = 0;
	while ((cur = str.find_first_of(separators, prev)) != std::string::npos) {
		tokens.push_back(str.substr(prev, cur - prev));
		prev = cur + 1;
	}
	if (prev < str.length()) {
		tokens.push_back(str.substr(prev, std::string::npos));
	}

	if (tokens.size() < pad_size) tokens.resize(pad_size);
	return std::move(tokens);
}

// double to string without scientific notation or trailing zeros
std::string StringHelper::formatDbl(const double & val) {
	// Reference: https://stackoverflow.com/a/15167203
	size_t len = std::snprintf(0, 0, formatDblf, val);
	std::string s(len + 1, 0);
	std::snprintf(&s[0], len + 1, formatDblf, val);
	// remove nul terminator
	s.pop_back();
	// remove trailing zeros
	s.erase(s.find_last_not_of('0') + 1, std::string::npos);
	// remove trailing point
	if (s.back() == '.') s.pop_back();
	return s;
}