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

				
		TEST_METHOD(assignment)
		{
			TimingGridBase tgb = TimingGridBase(1, 4, 4); 
			tgb[0][0][0].push_back(std::make_shared<NormalNoteOsu>(ho_nn_1));
			Assert::AreEqual(3, tgb[0][0][0][0]->getIndex());
		}

		TEST_METHOD(offset_1v)
		{
			TimingGridBase tgb = TimingGridBase(2, 4, 4); 

			std::vector<double> bpm_1v(8, 120.0);
			tgb.setBpm1DVector(bpm_1v);

			// 2 M / 4 B / 4 S

			// 500 (1 Beat)
			Assert::AreEqual(500.0, tgb.getOffsetAt(0,1,0)); 
			// 500 (1 Beat) + 125 (1 Snap)
			Assert::AreEqual(500.0 + 125.0, tgb.getOffsetAt(0,1,1)); 
			// 2000 (1 Measure) + 1000 (2 Beats) + 375 (3 Snaps)
			Assert::AreEqual(2000.0 + 1000.0 + 375.0, tgb.getOffsetAt(1,2,3)); 
		}
		TEST_METHOD(offset_2v)
		{
			TimingGridBase tgb = TimingGridBase(2, 4, 4); 

			std::vector<std::vector<double>> bpm_2v(2, std::vector<double>(4, 120.0));
			tgb.setBpm2DVector(bpm_2v);

			// 2 M / 4 B / 4 S

			// 500 (1 Beat)
			Assert::AreEqual(500.0, tgb.getOffsetAt(0,1,0)); 
			// 500 (1 Beat) + 125 (1 Snap)
			Assert::AreEqual(500.0 + 125.0, tgb.getOffsetAt(0,1,1)); 
			// 2000 (1 Measure) + 1000 (2 Beats) + 375 (3 Snaps)
			Assert::AreEqual(2000.0 + 1000.0 + 375.0, tgb.getOffsetAt(1,2,3)); 
		}
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