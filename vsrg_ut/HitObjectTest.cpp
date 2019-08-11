#include "stdafx.h"
#include "CppUnitTest.h"
#include <LongNote.h>
#include <NormalNote.h>
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
		LongNote ln_1 = LongNote(
			std::make_shared<NormalNote>(NormalNote(100.0, 5)),
			std::make_shared<NormalNote>(NormalNote(300.0, 5)));

		LongNote ln_2 = LongNote(
			std::make_shared<NormalNote>(NormalNote(200.0, 6)),
			std::make_shared<NormalNote>(NormalNote(400.0, 7)));

		LongNote ln_3 = LongNote(
			std::make_shared<NormalNote>(NormalNote(200.0, 5)),
			std::make_shared<NormalNote>(NormalNote(400.0, 5)));

		TEST_METHOD(getStartNote)
		{
			Assert::AreEqual(100.0, ln_1.getStartNote()->getOffsetMSec());

			SPtrHitObject start_ln = ln_1.getStartNote();
			start_ln->setOffsetMSec(200.0);

			Assert::AreEqual(200.0, ln_1.getStartNote()->getOffsetMSec());
		}
		TEST_METHOD(getEndNote)
		{
			Assert::AreEqual(300.0, ln_1.getEndNote()->getOffsetMSec());

			SPtrHitObject end_ln = ln_1.getEndNote();
			end_ln->setOffsetMSec(200.0);

			Assert::AreEqual(200.0, ln_1.getEndNote()->getOffsetMSec());
		}
		TEST_METHOD(Clone)
		{
			LongNote ln = ln_1.Clone();
			Assert::IsFalse(ln.getStartNote().get() == ln_1.getStartNote().get());
			Assert::IsFalse(ln.getEndNote().get() == ln_1.getEndNote().get());
		}
		TEST_METHOD(isOverlapping) {
			Assert::IsTrue(ln_1.isOverlapping(ln_3));
			// TODO: Implement
			// Assert::ExpectException<std::exception>(ln_1.isOverlapping(ln_2));
		}
		TEST_METHOD(isValid)
		{
			Assert::IsTrue(bool(LongNote( // Valid
				std::make_shared<NormalNote>(NormalNote(100.0, 5)),
				std::make_shared<NormalNote>(NormalNote(200.0, 5)))
				));
			Assert::IsFalse(bool(LongNote( // Invalid Note 2
				std::make_shared<NormalNote>(NormalNote(100.0, 5)),
				std::make_shared<NormalNote>(NormalNote(-200.0, 5)))
				));
			Assert::IsFalse(bool(LongNote( // Mismatched Columns
				std::make_shared<NormalNote>(NormalNote(100.0, 5)),
				std::make_shared<NormalNote>(NormalNote(200.0, 6)))
				));
			Assert::IsFalse(bool(LongNote( // Invalid Notes
				std::make_shared<NormalNote>(NormalNote(-100.0, 5)),
				std::make_shared<NormalNote>(NormalNote(-200.0, 5)))
				));
		}
		TEST_METHOD(isBetween)
		{
			Assert::IsFalse(ln_1.isBetween(100.0));
			Assert::IsTrue(ln_1.isBetween(200.0));
			Assert::IsTrue(ln_1.isBetween(300.0, true)); // Include Ends
		}
	};
}