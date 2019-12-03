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
			Logger::WriteMessage(std::to_string(tgb[0][0][0][0]->getIndex()).c_str());
		}

		TEST_METHOD(offset)
		{
			TimingGridBase tgb = TimingGridBase(1, 4, 4); 

			std::vector<std::vector<double>> bpm_2v(1, std::vector<double>(4, 120.0));
			tgb.setBpm2DVector(bpm_2v);
			Logger::WriteMessage(std::to_string(tgb.getOffsetAt(0,1,0)).c_str());
			Logger::WriteMessage(std::to_string(tgb.getOffsetAt(0,1,1)).c_str());
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