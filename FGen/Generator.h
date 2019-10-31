#pragma once

#include "stdafx.h"
#include <vector>
#include <qd/dd_real.h>

#include "Job.h"

namespace FGen
{
	const int BLOCK_WIDTH = 100;
	const int BLOCK_HEIGHT = 100;

	class Generator
	{
	public:

		inline int JobId() const
		{
			return m_Job.JobId();
		};

		inline Job Job() const
		{
			return m_Job;
		};

	private:
		const char* m_Name;
		FGen::Job m_Job;
		unsigned int m_targetIterationCount;
		dd_real* m_XPoints;
		dd_real* m_YPoints;
		double m_Log2;

	public:

		Generator(FGen::Job job);

		std::vector<unsigned int> GetCounts();
		std::vector<unsigned int> GetXCounts(int yPtr);

		void FillCounts(PointInt pos, unsigned int* counts, bool * doneFlags, double * zValues);
		void FillXCounts(PointInt pos, unsigned int* counts, bool * doneFlags, double * zValues, int yPtr);
		void FillXCounts2(PointInt pos, unsigned int* counts, bool * doneFlags, double * zValues, int yPtr);

		void FillXCountsTest(PointInt pos, unsigned int* counts, bool * doneFlags, double * zValues, int yPtr);

		std::vector<float> GetCountsF();
		std::vector<float>	GetXCountsF(int yPtr);

		~Generator();

	private:
		dd_real* GetXPoints();
		dd_real* GetYPoints();

		unsigned int GetCount(PointDd c, unsigned int maxIterations, unsigned int cntr, bool * done, PointDd * curVal);
		unsigned int GetCount2(dd_real cX, dd_real cY, double * curZ, unsigned int cntr, bool * done, dd_real xSquared, dd_real ySquared);

		float GetCountF(PointDd c, int maxIterations);

		double GetEscapeVelocity(dd_real cX, dd_real cY, dd_real zX, dd_real zY, dd_real xSquared, dd_real ySquared);
		PointDd GetPointDd(double * zValues);
		void PointDdToDoubleArray(PointDd z, double * zValues);


	};

}

