#include "stdafx.h"
#include "CppUnitTest.h"
#include <BaseObjects/Special/TimingGridBase.h>
#include <GameObjects/Osu/Singular/Hit/NormalNoteOsu.h>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace SpecialObject_
{		
	TEST_CLASS(TimingGridBase_)
	{
	public:
		// Initialize objects here
		NormalNoteOsu ho_nn_1 = NormalNoteOsu(100.0, 3);
		NormalNoteOsu ho_nn_2 = NormalNoteOsu(200.0, 4);

		TEST_METHOD(assignment_index)
		{
			TimingGridBase tgb = TimingGridBase(1, 4, 4);
			tgb.pushSnap(TimingGridIndex(0,0,1), std::make_shared<NormalNoteOsu>(ho_nn_1));
			Assert::AreEqual(3, tgb.getSnap(TimingGridIndex(0,0,1))[0]->getIndex());
		}
		TEST_METHOD(assignment_offset)
		{
			TimingGridBase tgb = TimingGridBase(1, 4, 4);
			tgb.pushSnap(125.0, std::make_shared<NormalNoteOsu>(ho_nn_1));
			Assert::AreEqual(3, tgb.getSnap(125.0)[0]->getIndex());
		}

		TEST_METHOD(offset_1v)
		{
			TimingGridBase tgb = TimingGridBase(2, 4, 4);

			std::vector<double> bpm_1v(8, 120.0);
			tgb.setBpm1DVector(bpm_1v);

			// 2 M / 4 B / 4 S

			// 500 (1 Beat)
			Assert::AreEqual(500.0, tgb.getOffset(0, 1, 0));
			// 500 (1 Beat) + 125 (1 Snap)
			Assert::AreEqual(500.0 + 125.0, tgb.getOffset(0, 1, 1));
			// 2000 (1 Measure) + 1000 (2 Beats) + 375 (3 Snaps)
			Assert::AreEqual(2000.0 + 1000.0 + 375.0, tgb.getOffset(1, 2, 3));
		}
		TEST_METHOD(offset_2v)
		{
			TimingGridBase tgb = TimingGridBase(2, 4, 4);

			std::vector<std::vector<double>> bpm_2v(2, std::vector<double>(4, 120.0));
			tgb.setBpm2DVector(bpm_2v);

			// 2 M / 4 B / 4 S

			// 500 (1 Beat)
			Assert::AreEqual(500.0, tgb.getOffset(0, 1, 0));
			// 500 (1 Beat) + 125 (1 Snap)
			Assert::AreEqual(500.0 + 125.0, tgb.getOffset(0, 1, 1));
			// 2000 (1 Measure) + 1000 (2 Beats) + 375 (3 Snaps)
			Assert::AreEqual(2000.0 + 1000.0 + 375.0, tgb.getOffset(1, 2, 3));
		}
		TEST_METHOD(getIndex_exact)
		{
			TimingGridBase tgb = TimingGridBase(2, 4, 4);

			std::vector<std::vector<double>> bpm_2v(2, std::vector<double>(4, 120.0));
			tgb.setBpm2DVector(bpm_2v);

			auto index = tgb.getIndex(500.0);
			Assert::AreEqual(0, (int) index.measure);
			Assert::AreEqual(1, (int) index.beat);
			Assert::AreEqual(0, (int) index.snap);

			index = tgb.getIndex(625.0);
			Assert::AreEqual(0, (int) index.measure);
			Assert::AreEqual(1, (int) index.beat);
			Assert::AreEqual(1, (int) index.snap);

			index = tgb.getIndex(3375.0);
			Assert::AreEqual(1, (int) index.measure);
			Assert::AreEqual(2, (int) index.beat);
			Assert::AreEqual(3, (int) index.snap);
		}
		TEST_METHOD(getIndex_fuzzy)
		{
			TimingGridBase tgb = TimingGridBase(2, 4, 4);

			std::vector<std::vector<double>> bpm_2v(2, std::vector<double>(4, 120.0));
			tgb.setBpm2DVector(bpm_2v);

			// One snap is 125ms, the match is a fuzzy round match

			auto index = tgb.getIndex(2005.0); // 2000 + 5 | 2125 - 120
			Assert::AreEqual(1, (int) index.measure);
			Assert::AreEqual(0, (int) index.beat);
			Assert::AreEqual(0, (int) index.snap);

			index = tgb.getIndex(1995.0); // 1875 + 120 | 2000 - 5
			Assert::AreEqual(1, (int) index.measure);
			Assert::AreEqual(0, (int) index.beat);
			Assert::AreEqual(0, (int) index.snap);

			index = tgb.getIndex(2062.5); // 2000 + 62.5 | 2125 - 62.5
			Assert::AreEqual(1, (int) index.measure);
			Assert::AreEqual(0, (int) index.beat);
			Assert::AreEqual(1, (int) index.snap);

			index = tgb.getIndex(1937.5); // 1875 + 62.5 | 2000 - 62.5
			Assert::AreEqual(1, (int) index.measure);
			Assert::AreEqual(0, (int) index.beat);
			Assert::AreEqual(0, (int) index.snap);
		}
		TEST_METHOD(getIndex_bad)
		{
			TimingGridBase tgb = TimingGridBase(2, 4, 4);

			std::vector<std::vector<double>> bpm_2v(2, std::vector<double>(4, 120.0));
			tgb.setBpm2DVector(bpm_2v);
			
			// One snap is 125ms, the match is a fuzzy round match
			Assert::ExpectException<std::out_of_range>([&](){tgb.getIndex(100000.0); });

		}
	};
	TEST_CLASS(TimingGridMeasure_)
	{
		NormalNoteOsu ho_nn_1 = NormalNoteOsu(100.0, 3);
		NormalNoteOsu ho_nn_2 = NormalNoteOsu(200.0, 4);
		TEST_METHOD(simplify_by1)
		{
			// 0000 0010 1000 0000
			// 0000 0010 1000 0000 Bad Divide
			TimingGridMeasure tgm = TimingGridMeasure(4, 4);
			tgm[1][2].push_back(std::make_shared<NormalNoteOsu>(ho_nn_1));
			tgm[2][0].push_back(std::make_shared<NormalNoteOsu>(ho_nn_1));
			tgm.simplify(1);
			Assert::AreEqual(3, tgm[1][2][0]->getIndex());
			Assert::AreEqual(3, tgm[2][0][0]->getIndex());
		}
		TEST_METHOD(simplify_by2)
		{
			// 0000 0010 1000 0000
			// 00   01   10   00
			TimingGridMeasure tgm = TimingGridMeasure(4, 4);
			tgm[1][2].push_back(std::make_shared<NormalNoteOsu>(ho_nn_1));
			tgm[2][0].push_back(std::make_shared<NormalNoteOsu>(ho_nn_1));
			tgm.simplify(2);
			Assert::AreEqual(3, tgm[1][1][0]->getIndex());
			Assert::AreEqual(3, tgm[2][0][0]->getIndex());
		}
		TEST_METHOD(simplify_by3bad)
		{
			// 0000 0010 1000 0000
			// 0000 0010 1000 0000 Bad Divide
			TimingGridMeasure tgm = TimingGridMeasure(4, 4);
			tgm[1][2].push_back(std::make_shared<NormalNoteOsu>(ho_nn_1));
			tgm[2][0].push_back(std::make_shared<NormalNoteOsu>(ho_nn_1));
			tgm.simplify(3);
			Assert::AreEqual(3, tgm[1][2][0]->getIndex());
			Assert::AreEqual(3, tgm[2][0][0]->getIndex());
		}
		TEST_METHOD(simplify_by3good)
		{
			// 000000 000100 100000 000000
			// 00     01     10     00
			TimingGridMeasure tgm = TimingGridMeasure(4, 6);
			tgm[1][3].push_back(std::make_shared<NormalNoteOsu>(ho_nn_1));
			tgm[2][0].push_back(std::make_shared<NormalNoteOsu>(ho_nn_1));
			tgm.simplify(3);
			Assert::AreEqual(3, tgm[1][1][0]->getIndex());
			Assert::AreEqual(3, tgm[2][0][0]->getIndex());
		}
	};
}