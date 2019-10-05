#include "stdafx.h"
#include "CppUnitTest.h"
#include <GameObjects/SM/Map/VsrgMapSM.h>
#include <GameObjects/SM/Singular/Hit/NormalNoteSM.h>
#include <GameObjects/SM/Singular/Hit/HoldNoteSM.h>
#include <GameObjects/SM/Singular/Event/TimingPointSM.h>
#include <iostream>
#include <filesystem>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace VsrgMapSM_
{
	TEST_CLASS(VsrgMapSM_)
	{
	public:

		std::string sm_wu_ev = "../test_files/SM/Wake Up - EDEN (Evening).sm";
		std::string sm_icf_ev = "../test_files/SM/I Can Fly In The Universe - Camellia (Evening).sm";
		std::string sm_532_mw = "../test_files/SM/532nm.sm";
		std::string sm_hpd_ln = "../test_files/SM/HappiDAAAaAAaAaAAA.sm";

		// Initialize objects here
		TEST_METHOD(LogDir) { // set to true to output dirs and file check
			if (false) {
				Logger::WriteMessage(std::filesystem::current_path().c_str());
				Assert::IsTrue(std::filesystem::exists(sm_wu_ev));
			}
		}
		TEST_METHOD(FileIO)
		{
			VsrgMapSM smmap = VsrgMapSM();
			smmap.loadFile(sm_wu_ev);

			auto eo_v = smmap.getEventObjectVector();

			//osumap.saveFile("test.osu", true);

			//osumap.saveAsVsrg("testing.vsrg", true);
			//osumap.saveAsVsrg("test.vsrg", true);
		}
	};
}