#include "stdafx.h"
#include "CppUnitTest.h"
#include <GameObjects/Osu/Singular/Event/ScrollPointOsu.h>
#include <GameObjects/Osu/Singular/Event/TimingPointOsu.h>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EventObject_
{
	// Initialize objects here
	ScrollPointOsu sp_1 = ScrollPointOsu(100.0, 1.0);
	ScrollPointOsu sp_2 = ScrollPointOsu(200.0, 2.0);

	TimingPointOsu tp_1 = TimingPointOsu(100.0, 120.0, 4.0, 4.0);
	TimingPointOsu tp_2 = TimingPointOsu(200.0, 250.0, 6.5, 4.0);

	TEST_CLASS(ScrollPoint_)
	{
	public:
		TEST_METHOD(ScrollPoint_validation)
		{
			Assert::IsFalse(bool(ScrollPointOsu(-10.0, 1.0)));
			Assert::IsFalse(bool(ScrollPointOsu(-10.0, -1.0)));
			Assert::IsTrue(bool(ScrollPointOsu(10.0, -1.0)));
			Assert::IsTrue(bool(ScrollPointOsu(10.0, 1.0)));
		}

		TEST_METHOD(ScrollPoint_arithmetic)
		{
			// Check Copy Arithmetic
			ScrollPointOsu sp_0 = sp_1;
			//Assert::AreEqual(1.0, sp_0.getScrollSpeedMult());
			//sp_0 = sp_1 + 2.0;
			//Assert::AreEqual(3.0, sp_0.getScrollSpeedMult());
			//sp_0 = sp_1 - 2.0;
			//Assert::AreEqual(-1.0, sp_0.getScrollSpeedMult());
			//sp_0 = sp_1 * 5.0;
			//Assert::AreEqual(5.0, sp_0.getScrollSpeedMult());
			//sp_0 = sp_1 / 5.0;
			//Assert::AreEqual(0.2, sp_0.getScrollSpeedMult());
			// Check Assignment Arithmetic
			sp_0 = sp_1;
			sp_0 += 2.0;
			Assert::AreEqual(3.0, sp_0.getScrollSpeedMult());
			sp_0 -= 2.0;
			Assert::AreEqual(1.0, sp_0.getScrollSpeedMult());
			sp_0 *= 5.0;
			Assert::AreEqual(5.0, sp_0.getScrollSpeedMult());
			sp_0 /= 10.0;
			Assert::AreEqual(0.5, sp_0.getScrollSpeedMult());

			// Check Function Arithmetic
			sp_0 = sp_1;
			Assert::IsTrue(sp_0.isPositive());
			Assert::IsFalse(sp_0.isNegative());
			Assert::IsTrue(sp_0.isApproximately(1.1, 0.1, true));
			Assert::IsFalse(sp_0.isApproximately(1.1, 0.1, false));
		}
	};
	TEST_CLASS(TimingPoint_)
	{
	public:
		TEST_METHOD(TimingPoint_validation)
		{
			Assert::IsFalse(TimingPointOsu(-100.0, 100.0, 4.0, 4.0));
			Assert::IsFalse(TimingPointOsu(100.0, -100.0, 4.0, 4.0));
			Assert::IsFalse(TimingPointOsu(100.0, 100.0, -4.0, 2.0));
			Assert::IsFalse(TimingPointOsu(100.0, 100.0, 4.0, -4.0));
			Assert::IsFalse(TimingPointOsu(100.0, 100.0, -4.0, -4.0));
			Assert::IsTrue(TimingPointOsu(100.0, 100.0, 4.0, 4.0));
			Assert::IsTrue(TimingPointOsu(0.0, 115.0, 0.3, 4.8));
		}

		TEST_METHOD(TimingPoint_duration)
		{
			// BPM: 120.0, 4/4
			Assert::AreEqual((1 / 120.0) * 60000, tp_1.getBeatDuration(1.0));
			Assert::AreEqual((1 / 120.0) * 60000 * 2.0, tp_1.getBeatDuration(2.0));
			Assert::AreEqual((1 / 120.0) * 60000 * 4.0, tp_1.getMeasureDuration(1.0));
			Assert::AreEqual((1 / 120.0) * 60000 * 4.0 * 2.0, tp_1.getMeasureDuration(2.0));

			// BPM: 250, 6.5/4
			Assert::AreEqual((1 / 250.0) * 60000, tp_2.getBeatDuration(1.0));
			Assert::AreEqual((1 / 250.0) * 60000 * 2.0, tp_2.getBeatDuration(2.0));
			Assert::AreEqual((1 / 250.0) * 60000 * 6.5, tp_2.getMeasureDuration(1.0));
			Assert::AreEqual((1 / 250.0) * 60000 * 6.5 * 2.0, tp_2.getMeasureDuration(2.0));
		}
	};
}