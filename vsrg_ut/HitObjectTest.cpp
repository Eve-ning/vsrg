#include "stdafx.h"
#include "CppUnitTest.h"
#include <GameObjects/Osu/Singular/Hit/LongNoteOsu.h>
#include <GameObjects/Osu/Singular/Hit/NormalNoteOsu.h>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace HitObject_
{		
	TEST_CLASS(NormalNote_)
	{
	public:
		// Initialize objects here
		NormalNoteOsu nn_1 = NormalNoteOsu(100.0, 3);
		NormalNoteOsu nn_2 = NormalNoteOsu(200.0, 4);

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
			Assert::IsFalse(bool(NormalNoteOsu(100.0, -10)));
			Assert::IsFalse(bool(NormalNoteOsu(-10.0, 10)));
			Assert::IsFalse(bool(NormalNoteOsu(-10.0, -100)));
			Assert::IsTrue(bool(NormalNoteOsu(10.0, 100)));
		}
	};

	TEST_CLASS(LongNote_)
	{
	public:
		LongNoteOsu ln_1 = LongNoteOsu(100.0, 5, 200.0);

		LongNoteOsu ln_2 = LongNoteOsu(200.0, 6, 200.0);

		LongNoteOsu ln_3 = LongNoteOsu(200.0, 5, 200.0);

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
			Assert::IsTrue(bool(LongNoteOsu(100.0, 5, 200.0)));
			Assert::IsFalse(bool(LongNoteOsu(100.0, -5, 200.0)));
			Assert::IsFalse(bool(LongNoteOsu(100.0, 5, -200.0)));
			Assert::IsFalse(bool(LongNoteOsu(100.0, -5, -200.0)));
		}
		TEST_METHOD(isBetween)
		{
			Assert::IsFalse(ln_1.isBetween(100.0));
			Assert::IsTrue(ln_1.isBetween(200.0));
			Assert::IsTrue(ln_1.isBetween(300.0, true)); // Include Ends
		}
	};
}