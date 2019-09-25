#include "stdafx.h"
#include "CppUnitTest.h"
#include <GameObjects/Osu/Singular/Hit/NormalNoteOsu.h>
#include <GameObjects/Osu/Singular/Hit/LongNoteOsu.h>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace HitObject_
{		
	TEST_CLASS(TimedObject_)
	{
	public:
		// Initialize objects here
		NormalNoteOsu ho_nn_1 = NormalNoteOsu(100.0, 3);
		NormalNoteOsu ho_nn_2 = NormalNoteOsu(200.0, 4);
		TEST_METHOD(TimedObject_arithmetic)
		{
			// The non-assignment operation needs a sptr
			auto nn_a = ho_nn_1.Clone();
			Assert::AreEqual(100.0, nn_a->getOffset());
			auto nn_b = nn_a->operator+(10.0);
			Assert::AreEqual(110.0, nn_b->getOffset());

			// The assignment operation doesn't need conversion
			ho_nn_1 += 20.0;
			Assert::AreEqual(120.0, ho_nn_1.getOffset());
		}

		TEST_METHOD(TimedObject_setGet)
		{
			auto nn_0 = ho_nn_1;
			
			// Check setters
			nn_0.setOffset(1.0, TimedObject::UnitScale::hour);
			Assert::AreEqual(3600000.0, nn_0.getOffset());
			nn_0.setOffset(1.0, TimedObject::UnitScale::minute);
			Assert::AreEqual(60000.0, nn_0.getOffset());
			nn_0.setOffset(1.0, TimedObject::UnitScale::second);
			Assert::AreEqual(1000.0, nn_0.getOffset());
			nn_0.setOffset(1.0);
			Assert::AreEqual(1.0, nn_0.getOffset());

			// Check getters

			nn_0.setOffset(1.0, TimedObject::UnitScale::hour);
			Assert::AreEqual(1.0, nn_0.getOffset(TimedObject::UnitScale::hour));
			nn_0.setOffset(1.0, TimedObject::UnitScale::hour);
			Assert::AreEqual(60.0, nn_0.getOffset(TimedObject::UnitScale::minute));
			nn_0.setOffset(1.0, TimedObject::UnitScale::hour);
			Assert::AreEqual(3600.0, nn_0.getOffset(TimedObject::UnitScale::second));
			nn_0.setOffset(1.0, TimedObject::UnitScale::hour);
			Assert::AreEqual(3600000.0, nn_0.getOffset(TimedObject::UnitScale::msecond));

			
		}
	};
}