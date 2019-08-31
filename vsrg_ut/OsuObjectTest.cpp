#include "stdafx.h"
#include "CppUnitTest.h"
#include <GameObjects/Osu/Map/VsrgMapOsu.h>
#include <iostream>
#include <filesystem>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace HitObject_
{		
	TEST_CLASS(VsrgMapOsu_)
	{
	public:

		std::string osu_dh_51 = "../test_files/Osu/xi - Double Helix (Level 51) [Nucleic].osu";
		// Initialize objects here
		TEST_METHOD(LogDir) { // set to true to output dirs and file check
			if (false) {
				Logger::WriteMessage(std::filesystem::current_path().c_str());
				Assert::IsTrue(std::filesystem::exists(osu_dh_51));
			}
		}
		TEST_METHOD(Create)
		{
			VsrgMapOsu osumap = VsrgMapOsu();
			osumap.loadFile(osu_dh_51);
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