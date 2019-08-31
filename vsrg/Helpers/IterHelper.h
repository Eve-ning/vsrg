#pragma once
namespace IterHelper
{
	std::string matchTag(
		std::vector<std::string>::const_iterator & begin,
		std::vector<std::string>::const_iterator end,
		const std::string & starts_with);

	std::vector<std::string> grabBetween(
		std::vector<std::string>::const_iterator begin,
		std::vector<std::string>::const_iterator end
	) {
		std::vector<std::string> out;
		while (begin != end) { out.push_back(*begin); begin++; }
		return std::move(out);
	}
};

