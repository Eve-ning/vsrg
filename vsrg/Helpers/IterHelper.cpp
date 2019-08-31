#include "stdafx.h"
#include "IterHelper.h"

std::string IterHelper::matchTag(std::vector<std::string>::const_iterator & begin, std::vector<std::string>::const_iterator end, const std::string & starts_with) {
	std::string str = "";
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
	std::cout << starts_with;
	BOOST_ASSERT_MSG(false, "Failed to match Tag");
	return str;
}
