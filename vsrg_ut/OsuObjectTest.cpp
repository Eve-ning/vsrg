#include "stdafx.h"
#include "CppUnitTest.h"
#include <GameObjects/Osu/Map/VsrgMapOsu.h>
#include <iostream>
#include <filesystem>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace VsrgMapOsu_
{		
	TEST_CLASS(VsrgMapOsu_)
	{
	public:

		std::string osu_fc_pd = "../test_files/Osu/Camellia - Fastest Crash ('Camellia's ''paroxysmal'' Energetic Hitech Remix) (paradoxus_) [Houkai].osu";
		// Initialize objects here
		TEST_METHOD(LogDir) { // set to true to output dirs and file check
			if (false) {
				Logger::WriteMessage(std::filesystem::current_path().c_str());
				Assert::IsTrue(std::filesystem::exists(osu_fc_pd));
			}
		}
		TEST_METHOD(Create)
		{
			VsrgMapOsu osumap = VsrgMapOsu();
			osumap.loadFile(osu_fc_pd);

			Logger::WriteMessage(osumap.params.artist_.c_str());
			Logger::WriteMessage(osumap.params.artist_u_.c_str());
			Logger::WriteMessage(osumap.params.audio_file_name_.c_str());
			Logger::WriteMessage(std::to_string(osumap.params.beatmap_id_).c_str());
			Logger::WriteMessage(std::to_string(osumap.params.beatmap_set_id_).c_str());
			Logger::WriteMessage(osumap.params.bg_file_name_.c_str());
			Logger::WriteMessage(osumap.params.creator_.c_str());
		}
			
		
	};
}