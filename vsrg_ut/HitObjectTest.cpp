#include "stdafx.h"
#include "CppUnitTest.h"
#include <LongNote.h>
#include <NormalNote.h>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace HitObject_
{		
	// Initialize objects here
	NormalNote nn_1 = NormalNote(100.0, 3);
	NormalNote nn_2 = NormalNote(200.0, 4);

	LongNote ln_1 = LongNote(std::make_shared<NormalNote>(NormalNote(100.0, 5)),
							 std::make_shared<NormalNote>(NormalNote(300.0, 5)));
	LongNote ln_2 = LongNote(std::make_shared<NormalNote>(NormalNote(200.0, 6)),
							 std::make_shared<NormalNote>(NormalNote(400.0, 7)));

	TEST_CLASS(NormalNote_)
	{
	public:
		TEST_METHOD(NormalNote_validation)
		{
			Assert::IsFalse(bool(NormalNote(100.0, -10)));
			Assert::IsFalse(bool(NormalNote(-10.0, 10)));
			Assert::IsFalse(bool(NormalNote(-10.0, -100)));
			Assert::IsFalse(bool(NormalNote(10.0, -100)));
		}

		TEST_METHOD(NormalNote_equals)
		{
			// isOverlapping is an alias to == operator
			Assert::IsTrue(nn_1 == nn_1);
			Assert::IsFalse(nn_1.isOverlapping(nn_2));
		}
	};
	TEST_CLASS(LongNote_)
	{
	public:
		TEST_METHOD(LongNote_equals)
		{
			Assert::IsTrue(ln_1 == ln_1);
			Assert::IsFalse(ln_1 == ln_2);
		}

		TEST_METHOD(LongNote_copy)
		{
			LongNote ln_0 = ln_1;
			SPtrHitObject ho_0 = ln_0.getStartNote();

			Assert::IsFalse(&ln_0 == &ln_1); // Addresses should be different
			Assert::IsTrue(ho_0.get() == ln_0.getStartNote().get()); // Extracted HO should have different addresses
			Assert::IsTrue(ln_0 == ln_1); // Element wise it should be the same
		}

		TEST_METHOD(LongNote_validation)
		{
			Assert::IsTrue(bool(ln_1));
			Assert::IsFalse(bool(ln_2)); // Bad Column
		}

		TEST_METHOD(LongNote_isBetween)
		{
			Assert::IsTrue(ln_1.isBetween(200.0));
			Assert::IsFalse(ln_1.isBetween(100.0));
			Assert::IsTrue(ln_1.isBetween(300.0, true));
		}
	};
}