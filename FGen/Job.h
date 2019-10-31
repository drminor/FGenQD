#pragma once
#include <qd/dd_real.h>

#include "PointDd.h"
#include "RectangleInt.h"

namespace FGen
{
	class Job
	{
	public:

		inline int JobId() const
		{
			return m_JobId;
		};

		inline RectangleInt Area() const
		{
			return m_Area;
		};

		inline PointDd Start() const
		{
			return m_Start;
		};

		inline PointDd End() const
		{
			return m_End;
		};

		inline SizeInt SamplePoints() const
		{
			return m_SamplePoints;
		};

		inline unsigned int MaxIterations() const
		{
			return m_MaxIterations;
		};

	private:
		int m_JobId;
		RectangleInt m_Area;
		PointDd m_Start;
		PointDd m_End;
		SizeInt m_SamplePoints;
		unsigned int m_MaxIterations;


	public:

		Job(int jobId, PointDd start, PointDd end, SizeInt samplePoints, unsigned int maxIterations, RectangleInt area);

		~Job();
	};


}



