#include "stdafx.h"
#include "CppUnitTest.h"
#include <GameObjects/Osu/Map/VsrgMapOsu.h>
#include <GameObjects/Osu/Singular/Hit/NormalNoteOsu.h>
#include <GameObjects/Osu/Singular/Hit/LongNoteOsu.h>
#include <GameObjects/Osu/Singular/Event/ScrollPointOsu.h>
#include <GameObjects/Osu/Singular/Event/TimingPointOsu.h>
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
		std::string osu_dh_51 = "../test_files/Osu/xi - Double Helix (Level 51) [Nucleic].osu";
		
		// Initialize objects here
		TEST_METHOD(LogDir) { // set to true to output dirs and file check
			if (false) {
				Logger::WriteMessage(std::filesystem::current_path().c_str());
				Assert::IsTrue(std::filesystem::exists(osu_fc_pd));
			}
		}
		TEST_METHOD(LoadFile)
		{
			VsrgMapOsu osumap = VsrgMapOsu();
			osumap.loadFile(osu_fc_pd);

			Assert::AreEqual(osumap.params.artist_.c_str(), "Camellia");
			Assert::AreEqual(osumap.params.audio_file_name_.c_str(), "audio.mp3");
			Assert::AreEqual(osumap.params.beatmap_id_, 1940322);
			Assert::AreEqual(osumap.params.beatmap_set_id_, 929005);
			Assert::AreEqual(osumap.params.creator_.c_str(), "paradoxus_");
			Assert::AreEqual(osumap.getHitObjectVector().getEarliestOffset(), 2315.);
			Assert::AreEqual(osumap.getEventObjectVector().getLatestOffset(), 1385015.);
			Assert::AreEqual(osumap.getEventObjectVector().getClassOnly<TimingPoint>()->at(0).getBpm(), 153.);
		}
		TEST_METHOD(NormalNoteOsu_) {
			NormalNoteOsu nn = NormalNoteOsu("36,192,1000,1,0,0:0:0:0:", 7);
			Assert::IsTrue(nn.getIndex() == 0);
			Assert::IsTrue(nn.getOffset() == 1000);
		}
		TEST_METHOD(LongNoteOsu_) {
			LongNoteOsu ln = LongNoteOsu("36,192,1000,128,0,3000:0:0:0:0:Te.wav", 7);
			Assert::IsTrue(ln.getIndex() == 0);
			Assert::IsTrue(ln.getOffset() == 1000);
			Assert::IsTrue(ln.getLength() == 2000);
		}		
		TEST_METHOD(ScrollPointOsu_) {
			ScrollPointOsu sp = ScrollPointOsu("100,-50,4,2,0,11,0,0");
			Assert::IsTrue(sp.getOffset() == 100);
			Assert::IsTrue(sp.getScrollSpeedMult() == 2.0);
			Assert::IsTrue(sp.params.volume_ == 11);
		}		
		TEST_METHOD(TimingPointOsu_) {
			TimingPointOsu tp = TimingPointOsu("200,300,4,2,0,11,1,0");
			Assert::IsTrue(tp.getBpm() == 200);
			Assert::IsTrue(tp.getOffset() == 200);
			Assert::IsTrue(tp.params.volume_ == 11);
		}
		
	};
}