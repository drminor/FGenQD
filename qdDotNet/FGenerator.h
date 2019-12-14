#pragma once

#include "../FGen/FGen.h"
#include "ManagedObject.h"
#include "Dd.h"
#include "FGenJob.h"

using namespace System;
namespace qdDotNet
{
	public ref class FGenerator
	{

	public:

		static int BLOCK_WIDTH = 100;
		static int BLOCK_HEIGHT = 100;

		FGenerator(FGenJob^ job);

		//array<UInt32>^ GetCounts();
		//array<UInt32>^ GetXCounts(int yPtr);

		void FillCounts(PointInt position, array<UInt32>^% xCounts, array<bool>^% doneFlags, array<double>^% zValues);
		//void FillXCounts(PointInt position, array<UInt32>^% xCounts, array<bool>^% doneFlags, array<double>^% zValues, int yPtr);
		//void FillXCounts2(PointInt position, array<UInt32>^% xCounts, array<bool>^% doneFlags, array<double>^% zValues, int yPtr);

		void FillXCountsTest(PointInt position, array<UInt32>^% xCounts, array<bool>^% doneFlags, array<double>^% zValues, int yPtr);


		//array<float>^ GetCountsF();
		//array<float>^ GetXCountsF(int yPtr);

		property FGenJob^ Job
		{
		public:
			FGenJob^ get()
			{
				return m_Job;
			}
		}

		virtual ~FGenerator()
		{
			CleanUp();
		}
		!FGenerator()
		{
			CleanUp();
		}

	private:

		FGenJob^ m_Job;
		FGen::Generator* m_Generator;

		inline void CleanUp() {
			if (m_Generator != nullptr)
			{
				delete m_Generator;
			}
		}

	};
}
