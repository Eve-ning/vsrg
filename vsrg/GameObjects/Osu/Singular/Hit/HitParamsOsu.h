#pragma once

/// This should define the game specific params of a osu note, such as local hitsound
struct HitParamsOsu
{
	static unsigned int indexToAxis(double index, unsigned int keys);
	static unsigned int axisToIndex(double axis, unsigned int keys);

	unsigned int hitsound_;
	unsigned int sample_;
	unsigned int addition_;
	unsigned int custom_;
	unsigned int volume_;
	std::string hitsound_file_;
};

