#include "stdafx.h"
#include "CppUnitTest.h"
#include <LongNote.h>
#include <NormalNote.h>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace HitObject_
{		
	TEST_CLASS(TimedObject_)
	{
	public:
		// Initialize objects here
		NormalNote ho_nn_1 = NormalNote(100.0, 3);
		NormalNote ho_nn_2 = NormalNote(200.0, 4);
		TEST_METHOD(TimedObject_arithmetic)
		{
			// The non-assignment operation needs a sptr
			auto nn_a = ho_nn_1.Clone();
			Assert::AreEqual(100.0, nn_a->getOffsetMSec());
			auto nn_b = nn_a->operator+(10.0);
			Assert::AreEqual(110.0, nn_b->getOffsetMSec());

			// The assignment operation doesn't need conversion
			ho_nn_1 += 20.0;
			Assert::AreEqual(120.0, ho_nn_1.getOffsetMSec());
		}

		TEST_METHOD(TimedObject_setGet)
		{
			auto nn_0 = ho_nn_1;
			
			// Check setters
			nn_0.setOffsetHour(1.0);
			Assert::AreEqual(3600000.0, nn_0.getOffsetMSec());
			nn_0.setOffsetMin(1.0);
			Assert::AreEqual(60000.0, nn_0.getOffsetMSec());
			nn_0.setOffsetSec(1.0);
			Assert::AreEqual(1000.0, nn_0.getOffsetMSec());
			nn_0.setOffsetMSec(1.0);
			Assert::AreEqual(1.0, nn_0.getOffsetMSec());

			// Check getters

			nn_0.setOffsetMSec(3600000.0);
			Assert::AreEqual(1.0, nn_0.getOffsetHour());
			nn_0.setOffsetMSec(3600000.0);
			Assert::AreEqual(60.0, nn_0.getOffsetMin());
			nn_0.setOffsetMSec(3600000.0);
			Assert::AreEqual(3600.0, nn_0.getOffsetSec());

			
		}
	};
}