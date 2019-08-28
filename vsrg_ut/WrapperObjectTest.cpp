#include "stdafx.h"
#include "CppUnitTest.h"

#include <TimedObjects/HitObjects/LongNote.h>
#include <TimedObjects/HitObjects/NormalNote.h>
#include <WrapperObjects/TimedObjects/HitObjectVector.h>

#include <TimedObjects/EventObjects/ScrollPoint.h>
#include <TimedObjects/EventObjects/TimingPoint.h>
#include <WrapperObjects/TimedObjects/EventObjectVector.h>

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

		LongNote ln_1 = LongNote(100.0, 5, 200.0);
		LongNote ln_2 = LongNote(200.0, 6, 200.0);
		HitObjectVector ho_v_1 = HitObjectVector();

		TEST_METHOD(HitObjectVector_vecOps)
		{
			ho_v_1.push_back(std::make_shared<NormalNote>(nn_1));
			ho_v_1.push_back(std::make_shared<NormalNote>(nn_2));

			Assert::AreEqual(size_t(2), ho_v_1.size());

			ho_v_1.pop_back();

			Assert::AreEqual(size_t(1), ho_v_1.size());

			ho_v_1.push_back(std::make_shared<LongNote>(ln_1));

			// Check for polymorphism
			Assert::AreEqual(size_t(2), ho_v_1.size());

			ho_v_1.clear();

			Assert::AreEqual(size_t(0), ho_v_1.size());
		}
	};
	
	TEST_CLASS(EventObjectVector_) {
		ScrollPoint sp_1 = ScrollPoint(100.0, 1.0);
		ScrollPoint sp_2 = ScrollPoint(200.0, 2.0);

		TimingPoint tp_1 = TimingPoint(100.0, 120.0, 4.0, 4.0);
		TimingPoint tp_2 = TimingPoint(200.0, 250.0, 6.5, 4.0);
		EventObjectVector eo_v_1 = EventObjectVector();
		TEST_METHOD(EventObjectVector_vecOps)
		{
			eo_v_1.push_back(std::make_shared<ScrollPoint>(sp_1));
			eo_v_1.push_back(std::make_shared<ScrollPoint>(sp_2));

			Assert::AreEqual(size_t(2), eo_v_1.size());

			eo_v_1.pop_back();

			Assert::AreEqual(size_t(1), eo_v_1.size());

			eo_v_1.push_back(std::make_shared<TimingPoint>(tp_1));

			// Check for polymorphism
			Assert::AreEqual(size_t(2), eo_v_1.size());

			eo_v_1.clear();

			Assert::AreEqual(size_t(0), eo_v_1.size());
		}
	};

	TEST_CLASS(TimedObjectVector_) {

		ScrollPoint sp_1 = ScrollPoint(100.0, 1.0);
		ScrollPoint sp_2 = ScrollPoint(200.0, 2.0);

		TimingPoint tp_1 = TimingPoint(100.0, 120.0, 4.0, 4.0);
		TimingPoint tp_2 = TimingPoint(200.0, 250.0, 6.5, 4.0);
		EventObjectVector eo_v_1 = EventObjectVector();

		TEST_METHOD(TimedObjectVector_getOffset) {
			std::vector<double> expected = { 100.0, 200.0, 100.0 };
			eo_v_1.push_back(sp_1.Clone());
			eo_v_1.push_back(sp_2.Clone());
			eo_v_1.push_back(tp_1.Clone());
			Assert::IsTrue(expected == eo_v_1.getOffsetVector());
			expected = { 100.0, 100.0, 200.0 };
			Assert::IsTrue(expected == eo_v_1.getOffsetVector(true));
		}
		TEST_METHOD(TimedObjectVector_getClassOnly) {
			eo_v_1.push_back(sp_1.Clone());
			eo_v_1.push_back(sp_2.Clone());
			eo_v_1.push_back(tp_1.Clone());
			// Filters out all Scroll Points
			std::vector<ScrollPoint> eo_v_2 = *eo_v_1.getClassOnly<ScrollPoint>();
			std::vector<TimingPoint> eo_v_3 = *eo_v_1.getClassOnly<TimingPoint>();
			Assert::AreEqual(size_t(2), eo_v_2.size());
			Assert::AreEqual(size_t(1), eo_v_3.size());
		}
	};
	
	TEST_CLASS(VsrgMap_) {

	};
}
	