#include "stdafx.h"
#include "IterHelper.h"

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

boost::tokenizer<boost::char_separator<char>> IterHelper::tokenize(const std::string & str, const char * separators) {
	boost::char_separator<char> sep(separators, "", boost::keep_empty_tokens);
	boost::tokenizer<boost::char_separator<char>> tokens(str, sep);
	return std::move(tokens);
}
