#include "stdafx.h"

#include "Generator.h"

namespace FGen
{
	Generator::Generator(FGen::Job job) : m_Job(job)
	{
		m_targetIterationCount = m_Job.MaxIterations();
		m_XPoints = GetXPoints();
		m_YPoints = GetYPoints();
		m_Log2 = std::log10(2);
	}

	std::vector<unsigned int>Generator::GetCounts()
	{
		int xSamples = m_Job.SamplePoints().W();
		int ySamples = m_Job.SamplePoints().H();

		int tSamples = xSamples * ySamples;
		std::vector<unsigned int> result; 
		//std::vector<unsigned short> result(tSamples);

		result.reserve(tSamples);

		int rPtr = 0;
		for (int j = 0; j < ySamples; j++) {
			dd_real yCord = m_YPoints[j];
			for (int i = 0; i < xSamples; i++) {
				dd_real xCord = m_XPoints[i];
				PointDd c = PointDd(xCord, yCord);
				//result[rPtr++] = Generator::GetCount(c, m_Job.MaxIterations());
				bool done = false;
				PointDd z = PointDd(0, 0);

				result.push_back(Generator::GetCount(c, m_targetIterationCount, 0, &done, &z));
			}
		}

		result.resize(tSamples);

		return result;
	}

	std::vector<unsigned int> Generator::GetXCounts(int yPtr)
	{
		std::vector<unsigned int> result;

		int xSamples = m_Job.SamplePoints().W();
		result.reserve(xSamples);

		dd_real yCord = m_YPoints[yPtr];
		for (int i = 0; i < xSamples; i++) {
			dd_real xCord = m_XPoints[i];
			PointDd c = PointDd(xCord, yCord);
			bool done = false;
			PointDd z = PointDd(0, 0);
			result.push_back(Generator::GetCount(c, m_targetIterationCount, 0, &done, &z));
		}

		result.resize(xSamples);

		return result;
	}

	void Generator::FillCounts(PointInt pos, unsigned int * counts, bool * doneFlags, double * zValues)
	{
		int startX = pos.X() * BLOCK_WIDTH;
		int startY = pos.Y() * BLOCK_HEIGHT;

		int resultPtr = 0;
		for (int j = 0; j < FGen::BLOCK_HEIGHT; j++) {
			
			dd_real yCord = m_YPoints[startY + j];

			for (int i = 0; i < FGen::BLOCK_WIDTH; i++) {
				dd_real xCord = m_XPoints[startX + i];
				PointDd c = PointDd(xCord, yCord);

				PointDd z = GetPointDd(&zValues[resultPtr * 4]);
				counts[resultPtr] = Generator::GetCount(c, m_targetIterationCount, counts[resultPtr], &doneFlags[resultPtr], &z);
				PointDdToDoubleArray(z, &zValues[resultPtr * 4]);

				resultPtr++;
			}
		}
	}

	void Generator::FillXCounts(PointInt pos, unsigned int * counts, bool * doneFlags, double * zValues, int yPtr)
	{
		int startX = pos.X() * BLOCK_WIDTH;
		int startY = pos.Y() * BLOCK_HEIGHT;

		int resultPtr = yPtr * BLOCK_WIDTH;

		dd_real yCord = m_YPoints[startY + yPtr];

		for (int i = 0; i < FGen::BLOCK_WIDTH; i++) {
			dd_real xCord = m_XPoints[startX + i];
			PointDd c = PointDd(xCord, yCord);

			PointDd z = GetPointDd(&zValues[resultPtr * 4]);
			counts[resultPtr] = Generator::GetCount(c, m_targetIterationCount, counts[resultPtr], &doneFlags[resultPtr], &z);
			PointDdToDoubleArray(z, &zValues[resultPtr * 4]);

			resultPtr++;
		}
	}

	void Generator::FillXCounts2(PointInt pos, unsigned int * counts, bool * doneFlags, double * zValues, int yPtr)
	{
		dd_real xSquared = dd_real(0);
		dd_real ySquared = dd_real(0);
		int startX = pos.X() * BLOCK_WIDTH;
		int startY = pos.Y() * BLOCK_HEIGHT;

		int resultPtr = yPtr * BLOCK_WIDTH;

		dd_real yCord = m_YPoints[startY + yPtr];

		for (int i = 0; i < FGen::BLOCK_WIDTH; i++) {
			dd_real xCord = m_XPoints[startX + i];
			counts[resultPtr] = Generator::GetCount2(xCord, yCord, &zValues[resultPtr * 4], counts[resultPtr], &doneFlags[resultPtr], xSquared, ySquared);
			resultPtr++;
		}
	}

	void Generator::FillXCountsTest(PointInt pos, unsigned int * counts, bool * doneFlags, double * zValues, int yPtr)
	{
		int startX = pos.X() * BLOCK_WIDTH;
		int startY = pos.Y() * BLOCK_HEIGHT;

		int resultPtr = yPtr * BLOCK_WIDTH;

		dd_real yCord = m_YPoints[startY + yPtr];

		for (int i = 0; i < FGen::BLOCK_WIDTH; i++) {
			dd_real xCord = m_XPoints[startX + i];
			PointDd c = PointDd(xCord, yCord);

			PointDd z = GetPointDd(&zValues[resultPtr * 4]);
			counts[resultPtr] = 3000 + i;
			doneFlags[resultPtr] = true;
			PointDdToDoubleArray(z, &zValues[resultPtr * 4]);
			resultPtr++;
		}
	}

	PointDd Generator::GetPointDd(double * zValues)
	{
		double xHi = zValues[0];
		double xLo = zValues[1];
		double yHi = zValues[2];
		double yLo = zValues[3];

		return PointDd(dd_real(xHi, xLo), dd_real(yHi, yLo));
	}

	void Generator::PointDdToDoubleArray(PointDd z, double * zValues) {
		zValues[0] = z.X()._hi();
		zValues[1] = z.X()._lo();
		zValues[2] = z.Y()._hi();
		zValues[3] = z.Y()._lo();
	}

	unsigned int Generator::GetCount(PointDd c, unsigned int maxIterations, unsigned int cntr, bool * done, PointDd * curVal) {

		dd_real cX = c.X();
		dd_real cY = c.Y();

		dd_real zX = curVal->X();
		dd_real zY = curVal->Y();

		dd_real xSquared = dd_real();
		dd_real ySquared = dd_real();

		double escapeVel = 0;
		//unsigned int cntr;
		//cntr /= 10000;
		cntr = 0;
		for (; cntr < maxIterations; cntr++) {
			zY = 2 * zX * zY + cY;
			zX = xSquared - ySquared + cX;
			xSquared = zX * zX;
			ySquared = zY * zY;

			if ((xSquared + ySquared) > 4) {
				//escapeVel = GetEscapeVelocity(cX, cY, zX, zY, xSquared, ySquared);
				*done = true;
				break;
			}
		}

		*curVal = PointDd(zX, zY);

		double both = cntr + escapeVel;
		both = std::round(10000 * both);

		return int(both);
	}

	unsigned int Generator::GetCount2(dd_real cX, dd_real cY, double * curZ, unsigned int cntr, bool * done, dd_real xSquared, dd_real ySquared)
	{
		dd_real zX = dd_real(curZ[0], curZ[1]);
		dd_real zY = dd_real(curZ[2], curZ[3]);

		xSquared.resetToZero();
		ySquared.resetToZero();

		double escapeVel = 0;
		//unsigned int cntr;
		//cntr /= 10000;
		cntr = 0;
		for (; cntr < m_targetIterationCount; cntr++) {
			zY = 2 * zX * zY + cY;
			zX = xSquared - ySquared + cX;
			xSquared = zX * zX;
			ySquared = zY * zY;

			if ((xSquared + ySquared) > 4) {

				//escapeVel = GetEscapeVelocity(cX, cY, zX, zY, xSquared, ySquared);
				*done = true;
				break;
			}
		}

		curZ[0] = zX._hi();
		curZ[1] = zX._lo();
		curZ[2] = zY._hi();
		curZ[3] = zY._lo();

		double both = cntr + escapeVel;
		both = std::round(10000 * both);

		return int(both);
	}


	//public double Iterate(DPoint c, ref DPoint z, ref int cntr, out bool done)
	//{
	//	done = false;
	//	double escapeVelocity = 0.0;

	//	_xSquared = 0;
	//	_ySquared = 0;

	//	for (; cntr < _maxIterations; cntr++)
	//	{
	//		z.Y = 2 * z.X * z.Y + c.Y;
	//		z.X = _xSquared - _ySquared + c.X;

	//		_xSquared = z.X * z.X;
	//		_ySquared = z.Y * z.Y;

	//		if ((_xSquared + _ySquared) > 4)
	//		{
	//			done = true;
	//			escapeVelocity = GetEscapeVelocity(z, c, _xSquared, _ySquared);
	//			//escapeVelocity = 0.4;
	//			break;
	//		}
	//	}

	//	return escapeVelocity;
	//}

	double Generator::GetEscapeVelocity(dd_real cX, dd_real cY, dd_real zX, dd_real zY, dd_real xSquared, dd_real ySquared) {

		int cntr;
		for (cntr = 0; cntr < 2; cntr++) {
			zY = 2 * zX * zY + cY;
			zX = xSquared - ySquared + cX;
			xSquared = zX * zX;
			ySquared = zY * zY;
		}

		dd_real ev = xSquared + ySquared;
		double evd = ev.toDouble();

		double modulus = std::log10(evd) / 2;
	    double nu = std::log10(modulus / m_Log2) / m_Log2;
		nu /= 4;

		if (nu > 1) {
			std::cout << "Nu has a value of " << nu << ", using 1 instead.";
			nu = 1;
		}

	    double result = 1 - nu;

	    return result;
	}

	std::vector<float>	Generator::GetCountsF()
	{
		int xSamples = m_Job.SamplePoints().W();
		int ySamples = m_Job.SamplePoints().H();

		int tSamples = xSamples * ySamples;
		std::vector<float> result;
		//std::vector<unsigned short> result(tSamples);

		result.reserve(tSamples);

		int rPtr = 0;
		for (int j = 0; j < ySamples; j++) {
			dd_real yCord = m_YPoints[j];
			for (int i = 0; i < xSamples; i++) {
				dd_real xCord = m_XPoints[i];
				PointDd c = PointDd(xCord, yCord);
				//result[rPtr++] = Generator::GetCount(c, m_Job.MaxIterations());
				result.push_back(Generator::GetCountF(c, m_targetIterationCount));
			}
		}

		result.resize(tSamples);

		return result;
	}

	std::vector<float>	Generator::GetXCountsF(int yPtr)
	{
		std::vector<float> result;

		int xSamples = m_Job.SamplePoints().W();
		result.reserve(xSamples);

		dd_real yCord = m_YPoints[yPtr];
		for (int i = 0; i < xSamples; i++) {
			dd_real xCord = m_XPoints[i];
			PointDd c = PointDd(xCord, yCord);
			result.push_back(Generator::GetCountF(c, m_targetIterationCount));
		}

		result.resize(xSamples);

		return result;
	}

	float Generator::GetCountF(PointDd c, int maxIterations) {

		dd_real cX = c.X();
		dd_real cY = c.Y();

		dd_real zX = dd_real();
		dd_real zY = dd_real();

		dd_real xSquared = dd_real();
		dd_real ySquared = dd_real();
		int cntr;
		for (cntr = 0; cntr < maxIterations; cntr++) {
			zY = 2 * zX * zY + cY;
			zX = xSquared - ySquared + cX;
			xSquared = zX * zX;
			ySquared = zY * zY;

			if ((xSquared + ySquared) > 4) {
				//escapeVelocity = GetEscapeVelocity(_z, c, _xSquared, _ySquared);
				break;
			}
		}

		float result = 0.0F + cntr;
		return result;
	}

	dd_real* Generator::GetXPoints()
	{
		int xSamples = m_Job.SamplePoints().W();
		int areaXSampleCnt = m_Job.Area().W() * BLOCK_WIDTH;

		dd_real* result = new dd_real[areaXSampleCnt];

		dd_real startC = m_Job.Start().X();
		dd_real diff = m_Job.End().X() - startC;

		int start = m_Job.Area().SX() * BLOCK_WIDTH;
		int end = start + areaXSampleCnt;

		int rPtr = 0;
		for (int i = start; i < end; i++)
		{
			double rat = (double)i / (double)xSamples;
			dd_real s = rat * diff;
			result[rPtr++] = startC + s;
		}

		return result;
	}

	dd_real* Generator::GetYPoints()
	{
		int ySamples = m_Job.SamplePoints().H();
		int areaYSampleCnt = m_Job.Area().H() * BLOCK_HEIGHT;

		dd_real* result = new dd_real[ySamples];

		dd_real startC = m_Job.End().Y();
		dd_real diff = m_Job.Start().Y() - startC;

		int start = m_Job.Area().SY() * BLOCK_HEIGHT;
		int end = start + areaYSampleCnt;

		int rPtr = 0;
		for (int i = start; i < end; i++)
		{
			double rat = (double)i / (double)ySamples;
			dd_real s = rat * diff;
			result[rPtr++] = startC + s;
		}

		return result;
	}

	Generator::~Generator()
	{
	}
}

