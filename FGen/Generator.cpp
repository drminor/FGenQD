#include "stdafx.h"

#include "FGen.h"
#include "GenPt.h"
#include "qpMath.h"

#include <iostream>
//#include <limits>
//#include <string>

namespace FGen
{
	Generator::Generator(Job job) : m_Job(job)
	{
		m_targetIterationCount = m_Job.MaxIterations();
		m_XPoints = GetXPoints();
		m_YPoints = GetYPoints();
		m_Log2 = std::log10(2);

		_cxCordHis = new double[BLOCK_WIDTH];
		_cxCordLos = new double[BLOCK_WIDTH];
		_cyCordHis = new double[BLOCK_WIDTH];
		_cyCordLos = new double[BLOCK_WIDTH];
	}

	Generator::~Generator()
	{
		delete[] m_XPoints;
		delete[] m_YPoints;
		delete[] _cxCordHis, _cxCordLos, _cyCordHis, _cyCordLos;
	}

	int Generator::GetJobId()
	{
		return m_Job.JobId();
	};

	FGen::Job Generator::GetJob()
	{
		return m_Job;
	};

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
			qp yCord = m_YPoints[j];
			for (int i = 0; i < xSamples; i++) {
				qp xCord = m_XPoints[i];
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

		qp yCord = m_YPoints[yPtr];
		for (int i = 0; i < xSamples; i++) {
			qp xCord = m_XPoints[i];
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
			
			qp yCord = m_YPoints[startY + j];

			for (int i = 0; i < FGen::BLOCK_WIDTH; i++) {
				qp xCord = m_XPoints[startX + i];
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

		qp yCord = m_YPoints[startY + yPtr];

		for (int i = 0; i < FGen::BLOCK_WIDTH; i++) {
			qp xCord = m_XPoints[startX + i];
			PointDd c = PointDd(xCord, yCord);

			PointDd z = GetPointDd(&zValues[resultPtr * 4]);
			counts[resultPtr] = Generator::GetCount(c, m_targetIterationCount, counts[resultPtr], &doneFlags[resultPtr], &z);
			PointDdToDoubleArray(z, &zValues[resultPtr * 4]);

			resultPtr++;
		}
	}

	void Generator::FillXCounts2(PointInt pos, unsigned int * counts, bool * doneFlags, double * zValues, int yPtr)
	{
		qp xSquared = qp(0);
		qp ySquared = qp(0);
		int startX = pos.X() * BLOCK_WIDTH;
		int startY = pos.Y() * BLOCK_HEIGHT;

		int resultPtr = yPtr * BLOCK_WIDTH;

		qp yCord = m_YPoints[startY + yPtr];

		for (int i = 0; i < FGen::BLOCK_WIDTH; i++) {
			qp xCord = m_XPoints[startX + i];
			counts[resultPtr] = Generator::GetCount2(xCord, yCord, &zValues[resultPtr * 4], counts[resultPtr], &doneFlags[resultPtr], xSquared, ySquared);
			resultPtr++;
		}

		for (int i = 0; i < FGen::BLOCK_WIDTH; i++) {
			qp xCord = m_XPoints[startX + i];
			counts[resultPtr] = Generator::GetCount2(xCord, yCord, &zValues[resultPtr * 4], counts[resultPtr], &doneFlags[resultPtr], xSquared, ySquared);
			resultPtr++;
		}
	}

	void Generator::FillCountsVec(PointInt pos, unsigned int * counts, bool * doneFlags, double * zValues)
	{
		qp xSquared = qp(0);
		qp ySquared = qp(0);
		int startX = pos.X() * BLOCK_WIDTH;
		int startY = pos.Y() * BLOCK_HEIGHT;

		//for (int i = 0; i < FGen::BLOCK_WIDTH; i++) {
		//	qp xCord = m_XPoints[startX + i];
		//	counts[resultPtr] = Generator::GetCount2(xCord, yCord, &zValues[resultPtr * 4], counts[resultPtr], &doneFlags[resultPtr], xSquared, ySquared);
		//	resultPtr++;
		//}

		qpMath * qpCalc = new qpMath(BLOCK_WIDTH);

		qp yCord = m_YPoints[startY];
		qpCalc->extendSingleQp(yCord, _cyCordHis, _cyCordLos);

		for (int i = 0; i < FGen::BLOCK_WIDTH; i++) {
			qp xCord = m_XPoints[startX + i];
			_cxCordHis[i] = xCord._hi();
			_cxCordLos[i] = xCord._lo();
		}

		GenPt * genPt = new GenPt(BLOCK_WIDTH, _cxCordHis, _cxCordLos, _cyCordHis, _cyCordLos);
		PointInt nextCoordIndex = PointInt(0, 1); // column 0 of row 1.

		bool complete = false;

		while (!complete)
		{
			Iterate(genPt);

			complete = true;
			bool morePts;
			bool * morePtsAddress = &morePts;
			for (int i = 0; i < BLOCK_WIDTH; i++)
			{
				if (genPt->IsEmpty(i)) continue;

				if (genPt->_sumSqsM4[i] > 0) {

					// Save the results
					int resultPtr = genPt->_resultIndexes[i].Y() * BLOCK_WIDTH + genPt->_resultIndexes[i].X();
					counts[resultPtr] = genPt->_cnt[i];
					doneFlags[resultPtr] = true;

					// Get the next pt to include in the active vector
					nextCoordIndex = GetNextCoordIndex(nextCoordIndex, morePts);

					if (morePts) {
						// Update the active vector with the new pt data.
						qp cY = m_YPoints[startY + nextCoordIndex.Y()];
						qp cX = m_XPoints[startX + nextCoordIndex.X()];
						genPt->SetC(cX, cY, i, nextCoordIndex);
						complete = false;
					}
					else {
						genPt->SetEmpty(i);
					}

				}
				else {
					genPt->_cnt[i]++;
					if (genPt->_cnt[i] == m_targetIterationCount) {

						// Save the results
						int resultPtr = genPt->_resultIndexes[i].Y() * BLOCK_WIDTH + genPt->_resultIndexes[i].X();
						counts[resultPtr] = genPt->_cnt[i];

						// Get the next pt to include in the active vector
						nextCoordIndex = GetNextCoordIndex(nextCoordIndex, morePts);

						if (morePts) {
							// Update the active vector with the new pt data.
							qp cY = m_YPoints[startY + nextCoordIndex.Y()];
							qp cX = m_XPoints[startX + nextCoordIndex.X()];
							genPt->SetC(cX, cY, i, nextCoordIndex);
							complete = false;
						}
						else {
							genPt->SetEmpty(i);
						}
					}
					else {
						complete = false;
					}
				}
			}
		}

		delete qpCalc;
		delete genPt;
	}

	PointInt Generator::GetNextCoordIndex(PointInt cur, bool &more)
	{
		if (cur.X() == BLOCK_WIDTH - 1) {
			if (cur.Y() == BLOCK_HEIGHT - 1) {
				more = false;
				return cur;
			}
			else {
				more = true;
				return PointInt(0, cur.Y() + 1);
			}
		}
		else {
			more = true;
			return PointInt(cur.X() + 1, cur.Y());
		}
	}

	void Generator::Iterate(GenPt * genPt)
	{
		//zY = 2 * zX * zY + cY;
		//zX = xSquared - ySquared + cX;
		//xSquared = zX * zX;
		//ySquared = zY * zY;
	}

	void Generator::FillXCountsTest(PointInt pos, unsigned int * counts, bool * doneFlags, double * zValues, int yPtr)
	{
		int startX = pos.X() * 3;
		int startY = pos.Y() * BLOCK_HEIGHT;

		int resultPtr = yPtr * BLOCK_WIDTH;

		qp yCord = m_YPoints[startY + yPtr];

		for (int i = 0; i < FGen::BLOCK_WIDTH; i++) {
			qp xCord = m_XPoints[startX + i];
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

		return PointDd(qp(xHi, xLo), qp(yHi, yLo));
	}

	void Generator::PointDdToDoubleArray(PointDd z, double * zValues) {
		zValues[0] = z.X()._hi();
		zValues[1] = z.X()._lo();
		zValues[2] = z.Y()._hi();
		zValues[3] = z.Y()._lo();
	}

	unsigned int Generator::GetCount(PointDd c, unsigned int maxIterations, unsigned int cntr, bool * done, PointDd * curVal) {

		qp cX = c.X();
		qp cY = c.Y();

		qp zX = curVal->X();
		qp zY = curVal->Y();

		qp xSquared = qp();
		qp ySquared = qp();

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

	unsigned int Generator::GetCount2(qp cX, qp cY, double * curZ, unsigned int cntr, bool * done, qp xSquared, qp ySquared)
	{
		qp zX = qp(curZ[0], curZ[1]);
		qp zY = qp(curZ[2], curZ[3]);

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

	double Generator::GetEscapeVelocity(qp cX, qp cY, qp zX, qp zY, qp xSquared, qp ySquared) {

		int cntr;
		for (cntr = 0; cntr < 2; cntr++) {
			zY = 2 * zX * zY + cY;
			zX = xSquared - ySquared + cX;
			xSquared = zX * zX;
			ySquared = zY * zY;
		}

		qp ev = xSquared + ySquared;
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
			qp yCord = m_YPoints[j];
			for (int i = 0; i < xSamples; i++) {
				qp xCord = m_XPoints[i];
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

		qp yCord = m_YPoints[yPtr];
		for (int i = 0; i < xSamples; i++) {
			qp xCord = m_XPoints[i];
			PointDd c = PointDd(xCord, yCord);
			result.push_back(Generator::GetCountF(c, m_targetIterationCount));
		}

		result.resize(xSamples);

		return result;
	}

	float Generator::GetCountF(PointDd c, int maxIterations) {

		qp cX = c.X();
		qp cY = c.Y();

		qp zX = qp();
		qp zY = qp();

		qp xSquared = qp();
		qp ySquared = qp();
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

	qp* Generator::GetXPoints()
	{
		int xSamples = m_Job.SamplePoints().W();
		int areaXSampleCnt = m_Job.Area().W() * BLOCK_WIDTH;

		//qp* result = new qp[areaXSampleCnt];

		qp startC = m_Job.Start().X();
		//qp diff = m_Job.End().X() - startC;
		qp endC = m_Job.End().X();

		int start = m_Job.Area().SX() * BLOCK_WIDTH;
		int end = start + areaXSampleCnt;

		qp* result = GetPoints(xSamples, areaXSampleCnt, start, end, startC, endC);

		//int rPtr = 0;
		//for (int i = start; i < end; i++)
		//{
		//	double rat = (double)i / (double)xSamples;
		//	qp s = rat * diff;
		//	result[rPtr++] = startC + s;
		//}

		return result;
	}

	qp* Generator::GetYPoints()
	{
		int ySamples = m_Job.SamplePoints().H();
		int areaYSampleCnt = m_Job.Area().H() * BLOCK_HEIGHT;

		//qp* result = new qp[ySamples];

		qp startC = m_Job.End().Y();
		//qp diff = m_Job.Start().Y() - startC;
		qp endC = m_Job.Start().Y();

		int start = m_Job.Area().SY() * BLOCK_HEIGHT;
		int end = start + areaYSampleCnt;

		qp* result = GetPoints(ySamples, areaYSampleCnt, start, end, startC, endC);

		//int rPtr = 0;
		//for (int i = start; i < end; i++)
		//{
		//	double rat = (double)i / (double)ySamples;
		//	qp s = rat * diff;
		//	result[rPtr++] = startC + s;
		//}

		return result;
	}

	qp* Generator::GetPoints(int sampleCnt, int width, int areaStart, int areaEnd, qp startC, qp endC)
	{
		qp* result = new qp[width];

		//qp diff = endC - startC;

		qpMath * qpCalc = new qpMath();
		qp diff = qpCalc->getDiff(endC, startC);

		double * diff_his = new double[width];
		double * diff_los = new double[width];
		double * inc_his = new double[width];
		double * inc_los = new double[width];

		//int rPtr = 0;
		//for (int i = areaStart; i < areaEnd; i++)
		//{
		//	double rat = (double)i / (double)sampleCnt;
		//	qp s = rat * diff;
		//	result[rPtr++] = startC + s;
		//}

		double * rats = new double[sampleCnt];

		int rPtr = 0;
		for (int i = areaStart; i < areaEnd; i++)
		{
			rats[rPtr++] = (double)i / (double)sampleCnt;
		}

		qpMath * qpVecCalc = new qpMath(width);

		qpVecCalc->extendSingleQp(diff, diff_his, diff_los);
		qpVecCalc->mulQpByD(diff_his, diff_los, rats, inc_his, inc_los);

		double * startC_his = new double[width];
		double * startC_los = new double[width];

		qpVecCalc->extendSingleQp(startC, startC_his, startC_los);

		qpVecCalc->addQps(inc_his, inc_los, startC_his, startC_los);

		//qpVecCalc->makeQpVector(inc_his, inc_los, result);

		delete[] diff_his, diff_los, startC_his, startC_los;
		delete[] inc_his, inc_los;

		delete qpCalc;
		delete qpVecCalc;
		//delete[] diff_his, diff_los, startC_his, startC_los;

		return result;
	}
}

