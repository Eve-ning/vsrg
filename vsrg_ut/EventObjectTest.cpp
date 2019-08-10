#include "stdafx.h"
#include "CppUnitTest.h"
#include <ScrollPoint.h>
#include <TimingPoint.h>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EventObject_
{
	// Initialize objects here
	ScrollPoint sp_1 = ScrollPoint(100.0, 1.0);
	ScrollPoint sp_2 = ScrollPoint(200.0, 2.0);

	TimingPoint tp_1 = TimingPoint(100.0, 120.0, 4.0, 4.0);
	TimingPoint tp_2 = TimingPoint(200.0, 250.0, 6.5, 4.0);

	TEST_CLASS(ScrollPoint_)
	{
	public:
		TEST_METHOD(ScrollPoint_validation)
		{
			Assert::IsFalse(bool(ScrollPoint(-10.0, 1.0)));
			Assert::IsFalse(bool(ScrollPoint(-10.0, -1.0)));
			Assert::IsTrue(bool(ScrollPoint(10.0, -1.0)));
			Assert::IsTrue(bool(ScrollPoint(10.0, 1.0)));
		}

		TEST_METHOD(ScrollPoint_arithmetic)
		{
			// Check Copy Arithmetic
			ScrollPoint sp_0 = sp_1;
			Assert::AreEqual(1.0, sp_0.getScrollSpeedMult());
			sp_0 = sp_1 + 2.0;
			Assert::AreEqual(3.0, sp_0.getScrollSpeedMult());
			sp_0 = sp_1 - 2.0;
			Assert::AreEqual(-1.0, sp_0.getScrollSpeedMult());
			sp_0 = sp_1 * 5.0;
			Assert::AreEqual(5.0, sp_0.getScrollSpeedMult());
			sp_0 = sp_1 / 5.0;
			Assert::AreEqual(0.2, sp_0.getScrollSpeedMult());
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
			Assert::IsFalse(TimingPoint(-100.0, 100.0, 4.0, 4.0));
			Assert::IsFalse(TimingPoint(100.0, -100.0, 4.0, 4.0));
			Assert::IsFalse(TimingPoint(100.0, 100.0, -4.0, 2.0));
			Assert::IsFalse(TimingPoint(100.0, 100.0, 4.0, -4.0));
			Assert::IsFalse(TimingPoint(100.0, 100.0, -4.0, -4.0));
			Assert::IsTrue(TimingPoint(100.0, 100.0, 4.0, 4.0));
			Assert::IsTrue(TimingPoint(0.0, 115.0, 0.3, 4.8));
		}

		TEST_METHOD(TimingPoint_duration)
		{
			// BPM: 120.0, 4/4
			Assert::AreEqual((1 / 120.0) * 60000, tp_1.getBeatDurationMSec(1.0));
			Assert::AreEqual((1 / 120.0) * 60000 * 2.0, tp_1.getBeatDurationMSec(2.0));
			Assert::AreEqual((1 / 120.0) * 60000 * 4.0, tp_1.getMeasureDurationMSec(1.0));
			Assert::AreEqual((1 / 120.0) * 60000 * 4.0 * 2.0, tp_1.getMeasureDurationMSec(2.0));

			// BPM: 250, 6.5/4
			Assert::AreEqual((1 / 250.0) * 60000, tp_2.getBeatDurationMSec(1.0));
			Assert::AreEqual((1 / 250.0) * 60000 * 2.0, tp_2.getBeatDurationMSec(2.0));
			Assert::AreEqual((1 / 250.0) * 60000 * 6.5, tp_2.getMeasureDurationMSec(1.0));
			Assert::AreEqual((1 / 250.0) * 60000 * 6.5 * 2.0, tp_2.getMeasureDurationMSec(2.0));
		}
	};
}