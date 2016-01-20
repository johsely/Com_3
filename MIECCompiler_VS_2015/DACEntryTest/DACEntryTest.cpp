#include "stdafx.h"
#include "CppUnitTest.h"
#include "../MIECCompiler/DACEntry.h"
#include <iostream>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace DACEntryTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			stringstream ost;
			DACEntry dacEntry(eAdd, nullptr, nullptr);
			dacEntry.Print(ost);
			Assert::AreEqual((int)eAdd, (int)dacEntry.GetOpKind());
			Assert::AreEqual(0, (int)dacEntry.GetArg1());
			Assert::AreEqual(0, (int)dacEntry.GetArg2());

		}


	};
}