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
			smmap.loadFile(sm_icf_ev);
			smmap.loadFile(sm_532_mw);
			smmap.loadFile(sm_hpd_ln);







			//Assert::AreEqual("Camellia", osumap.params.artist_.c_str());
			//Assert::AreEqual("audio.mp3", osumap.params.audio_path_.c_str());
			//Assert::AreEqual(1940322, osumap.params.beatmap_id_);
			//Assert::AreEqual(929005, osumap.params.beatmap_set_id_);
			//Assert::AreEqual("paradoxus_", osumap.params.creator_.c_str());
			//Assert::AreEqual(2315., osumap.getHitObjectVector()->getEarliestOffset());
			//Assert::AreEqual(1385015., osumap.getEventObjectVector()->getLatestOffset());
			//Assert::AreEqual(153., osumap.getEventObjectVector()->getClassOnly<TimingPointOsu>()[0].getBpm());

			//osumap.saveFile("test.osu", true);

			//osumap.saveAsVsrg("testing.vsrg", true);
			//osumap.saveAsVsrg("test.vsrg", true);
		}
	};
}