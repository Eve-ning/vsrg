#include "stdafx.h"
#include "HitObjectVectorOsu.h"
#include "GameObjects/Osu/Singular/Hit/LongNoteOsu.h"
#include "GameObjects/Osu/Singular/Hit/NormalNoteOsu.h"

HitObjectVectorOsu::HitObjectVectorOsu()
{
}


HitObjectVectorOsu::~HitObjectVectorOsu()
{
}

void HitObjectVectorOsu::fromYaml(const YAML::Node & node) {
	for (const auto & entry : node["long_note"])
		to_v_.push_back(std::make_shared<LongNoteOsu>(LongNoteOsu(entry)));
	for (const auto & entry : node["normal_note"])
		to_v_.push_back(std::make_shared<NormalNoteOsu>(NormalNoteOsu(entry)));
}
