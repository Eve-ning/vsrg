#include "stdafx.h"
#include "CppUnitTest.h"
#include <BaseObjects/Singular/Hit/LongNote.h>
#include <BaseObjects/Singular/Hit/NormalNote.h>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace HitObject_
{		
	TEST_CLASS(NormalNote_)
	{
	public:
		// Initialize objects here
		NormalNote nn_1 = NormalNote(100.0, 3);
		NormalNote nn_2 = NormalNote(200.0, 4);

		TEST_METHOD(Clone) {
			SPtrTimedObject sptr_nn = nn_1.Clone();
			Assert::IsFalse(sptr_nn.get() == &nn_1);
		}
		TEST_METHOD(getIndex) {
			Assert::AreEqual(3, nn_1.getIndex());
		}
		TEST_METHOD(isOverlapping) {
			Assert::IsTrue(nn_1.isOverlapping(nn_1));
			Assert::IsFalse(nn_1.isOverlapping(nn_2));
		}
		TEST_METHOD(isValid) {
			Assert::IsFalse(bool(NormalNote(100.0, -10)));
			Assert::IsFalse(bool(NormalNote(-10.0, 10)));
			Assert::IsFalse(bool(NormalNote(-10.0, -100)));
			Assert::IsTrue(bool(NormalNote(10.0, 100)));
		}
	};

	TEST_CLASS(LongNote_)
	{
	public:
		LongNote ln_1 = LongNote(100.0, 5, 200.0);

		LongNote ln_2 = LongNote(200.0, 6, 200.0);

		LongNote ln_3 = LongNote(200.0, 5, 200.0);

		TEST_METHOD(Clone)
		{
			SPtrTimedObject ln = ln_1.Clone();
			Assert::IsFalse(ln.get() == &ln_1);
		}
		TEST_METHOD(isOverlapping) {
			Assert::IsTrue(ln_1.isOverlapping(ln_3));
		}
		TEST_METHOD(isValid)
		{
			Assert::IsTrue(bool(LongNote(100.0, 5, 200.0)));
			Assert::IsFalse(bool(LongNote(100.0, -5, 200.0)));
			Assert::IsFalse(bool(LongNote(100.0, 5, -200.0)));
			Assert::IsFalse(bool(LongNote(100.0, -5, -200.0)));
		}
		TEST_METHOD(isBetween)
		{
			Assert::IsFalse(ln_1.isBetween(100.0));
			Assert::IsTrue(ln_1.isBetween(200.0));
			Assert::IsTrue(ln_1.isBetween(300.0, true)); // Include Ends
		}
	};
}