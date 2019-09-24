#pragma once
#include <boost/spirit/include/classic.hpp>

using namespace boost::spirit::classic;

class VsrgMapParser
{
public:
	VsrgMapParser();
	~VsrgMapParser();
private:

	rule<> alnum_rule = alnum_p | ch_p('_') >> *(alnum_p | ch_p('_'));
	rule<> blanks_rule = *blank_p;
	

};

