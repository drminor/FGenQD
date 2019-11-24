#pragma once

#ifdef FGEN_EXPORTS
#define FGEN_API __declspec(dllexport)
#else
#define FGEN_API __declspec(dllimport)

#endif

#include "stdafx.h"
#include <vector>
#include "Job.h"
#include "qp.h"

namespace FGen
{
	const int BLOCK_WIDTH = 100;
	const int BLOCK_HEIGHT = 100;

	class FGEN_API Generator
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
		qp* m_XPoints;
		qp* m_YPoints;
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
		qp * GetXPoints();
		qp * GetYPoints();

		qp * GetPoints(int sampleCnt, int width, int areaStart, int areaEnd, qp startC, qp diff);

		

		unsigned int GetCount(PointDd c, unsigned int maxIterations, unsigned int cntr, bool * done, PointDd * curVal);
		unsigned int GetCount2(qp cX, qp cY, double * curZ, unsigned int cntr, bool * done, qp xSquared, qp ySquared);

		float GetCountF(PointDd c, int maxIterations);

		double GetEscapeVelocity(qp cX, qp cY, qp zX, qp zY, qp xSquared, qp ySquared);
		PointDd GetPointDd(double * zValues);
		void PointDdToDoubleArray(PointDd z, double * zValues);
	};

}

