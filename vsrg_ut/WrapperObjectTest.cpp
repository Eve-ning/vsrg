#include "stdafx.h"
#include "CppUnitTest.h"
#include <LongNote.h>
#include <NormalNote.h>
#include <HitObjectVector.h>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace WrapperObject_
{		
	// Initialize objects here
	NormalNote nn_1 = NormalNote(100.0, 3);
	NormalNote nn_2 = NormalNote(200.0, 4);

	LongNote ln_1 = LongNote(std::make_shared<NormalNote>(NormalNote(100.0, 5)),
							 std::make_shared<NormalNote>(NormalNote(300.0, 5)));
	LongNote ln_2 = LongNote(std::make_shared<NormalNote>(NormalNote(200.0, 6)),
							 std::make_shared<NormalNote>(NormalNote(400.0, 7)));

	HitObjectVector hov_1 = HitObjectVector();
	hov_1.push_back(std::make_shared<HitObject>(nn_1));


	TEST_CLASS(HitObjectVector_)
	{
	public:
		TEST_METHOD(HitObjectVector_copy)
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
	
}