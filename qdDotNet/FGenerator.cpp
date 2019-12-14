#include "stdafx.h"
#include "FGenerator.h"
#include "../FGen/FGen.h"
#include "FGenJob.h"

namespace qdDotNet
{

	FGenerator::FGenerator(FGenJob^ job)
	{
		FGen::Job* nJob = (new FGen::Job(
			job->JobId,
			FGen::PointDd(job->Start.X().ToQp(), job->Start.Y().ToQp()),
			FGen::PointDd(job->End.X().ToQp(), job->End.Y().ToQp()),
			FGen::SizeInt(job->SamplePoints.W(), job->SamplePoints.H()),
			job->MaxIterations,
			FGen::RectangleInt(job->Area.X(), job->Area.Y(), job->Area.W(), job->Area.H())
		));

		m_Generator = new FGen::Generator(*nJob);
		m_Job = job;
	}

	//array<UInt32>^ FGenerator::GetCounts()
	//{
	//	std::vector<unsigned int> tempVec = m_Generator->GetCounts();
	//	const int SIZE = tempVec.size();
	//	array<UInt32> ^tempArr = gcnew array<UInt32>(SIZE);
	//	for (int i = 0; i < SIZE; i++)
	//	{
	//		tempArr[i] = tempVec[i];
	//	}
	//	return tempArr;
	//}

	//array<UInt32>^ FGenerator::GetXCounts(int yPtr)
	//{
	//	std::vector<unsigned int> tempVec = m_Generator->GetXCounts(yPtr);
	//	const int SIZE = tempVec.size();
	//	array<UInt32> ^tempArr = gcnew array<UInt32>(SIZE);
	//	for (int i = 0; i < SIZE; i++)
	//	{
	//		tempArr[i] = tempVec[i];
	//	}
	//	return tempArr;
	//}

	void FGenerator::FillCounts(PointInt position, array<UInt32>^% xCounts, array<bool>^% doneFlags, array<double>^% zValues)
	{
		FGen::PointInt pos = FGen::PointInt(position.X(), position.Y());
		pin_ptr<unsigned int> pCnts = &xCounts[0];
		pin_ptr<bool> pDfs = &doneFlags[0];
		pin_ptr<double> pZVals = &zValues[0];

		//m_Generator->FillCounts(pos, pCnts, pDfs, pZVals);
		m_Generator->FillCountsVec(pos, pCnts, pDfs, pZVals);
	}

	//void FGenerator::FillXCounts(PointInt position, array<UInt32>^% xCounts, array<bool>^% doneFlags, array<double>^% zValues, int yPtr)
	//{
	//	FGen::PointInt pos = FGen::PointInt(position.X(), position.Y());
	//	pin_ptr<unsigned int> pCnts = &xCounts[0];
	//	pin_ptr<bool> pDfs = &doneFlags[0];
	//	pin_ptr<double> pZVals = &zValues[0];

	//	m_Generator->FillXCounts(pos, pCnts, pDfs, pZVals, yPtr);
	//}

	//void FGenerator::FillXCounts2(PointInt position, array<UInt32>^% xCounts, array<bool>^% doneFlags, array<double>^% zValues, int yPtr)
	//{
	//	FGen::PointInt pos = FGen::PointInt(position.X(), position.Y());
	//	pin_ptr<unsigned int> pCnts = &xCounts[0];
	//	pin_ptr<bool> pDfs = &doneFlags[0];
	//	pin_ptr<double> pZVals = &zValues[0];

	//	m_Generator->FillXCounts2(pos, pCnts, pDfs, pZVals, yPtr);
	//}

	void FGenerator::FillXCountsTest(PointInt position, array<UInt32>^% xCounts, array<bool>^% doneFlags, array<double>^% zValues, int yPtr)
	{
		FGen::PointInt pos = FGen::PointInt(position.X(), position.Y());
		pin_ptr<unsigned int> pCnts = &xCounts[0];
		pin_ptr<bool> pDfs = &doneFlags[0];
		pin_ptr<double> pZVals = &zValues[0];

		m_Generator->FillXCountsTest(pos, pCnts, pDfs, pZVals, yPtr);
	}

	//array<float>^ FGenerator::GetCountsF()
	//{
	//	std::vector<float> tempVec = m_Generator->GetCountsF();
	//	const int SIZE = tempVec.size();
	//	array<float> ^tempArr = gcnew array<float>(SIZE);
	//	for (int i = 0; i < SIZE; i++)
	//	{
	//		tempArr[i] = tempVec[i];
	//	}
	//	return tempArr;
	//}

	//array<float>^ FGenerator::GetXCountsF(int yPtr)
	//{
	//	std::vector<float> tempVec = m_Generator->GetXCountsF(yPtr);
	//	const int SIZE = tempVec.size();
	//	array<float> ^tempArr = gcnew array<float>(SIZE);
	//	for (int i = 0; i < SIZE; i++)
	//	{
	//		tempArr[i] = tempVec[i];
	//	}
	//	return tempArr;
	//}

	
}

