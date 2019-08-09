#include "stdafx.h"
#include "CppUnitTest.h"
#include <LongNote.h>
#include <NormalNote.h>
#include <HitObjectVector.h>
#include <iostream>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace WrapperObjct_
{		
	TEST_CLASS(HitObjectVector_)
	{
	public:
		// Initialize objects here
		NormalNote nn_1 = NormalNote(100.0, 3);
		NormalNote nn_2 = NormalNote(200.0, 4);

		LongNote ln_1 = LongNote(std::make_shared<NormalNote>(NormalNote(100.0, 5)),
								 std::make_shared<NormalNote>(NormalNote(300.0, 5)));
		LongNote ln_2 = LongNote(std::make_shared<NormalNote>(NormalNote(200.0, 6)),
								 std::make_shared<NormalNote>(NormalNote(400.0, 7)));
		HitObjectVector ho_v_1 = HitObjectVector();
		TEST_METHOD(HitObjectVector_vec_ops)
		{
			ho_v_1.push_back(std::make_shared<HitObject>(nn_1));
			ho_v_1.push_back(std::make_shared<HitObject>(nn_2));

			Assert::AreEqual(size_t(2), ho_v_1.size());

			ho_v_1.pop_back();

			Assert::AreEqual(size_t(1), ho_v_1.size());

			ho_v_1.push_back(std::make_shared<HitObject>(ln_1));

			// Check for polymorphism
			Assert::AreEqual(size_t(2), ho_v_1.size());

			ho_v_1.clear();

			Assert::AreEqual(size_t(0), ho_v_1.size());
		}

	};

}
	