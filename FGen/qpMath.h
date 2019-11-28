#pragma once


#ifdef FGEN_EXPORTS
#define FGEN_API __declspec(dllexport)
#else
#define FGEN_API __declspec(dllimport)
#endif

#include "qp.h"
#include "../QPVec/qpvec.h"

using namespace qpvec;

namespace FGen
{
	class qpMath
	{

	public:
		qpMath();
		qpMath(int len);

		qp getDiff(qp end, qp start);

		void addQps(double * ahis, double * alos, double * bhis, double * blos, double * rhis, double * rlos);
		void subQps(double * ahis, double * alos, double * bhis, double * blos, double * rhis, double * rlos);
		void subDFromQps(double * ahis, double * alos, double * b, double * rhis, double * rlos);

		void mulQpByD(double * his, double * los, double * f, double * rhis, double * rlos);
		void mulQpByQp(double * ahis, double * alos, double * bhis, double * blos, double * rhis, double * rlos);

		void sqrQp(double * ahis, double * alos, double * rhis, double * rlos);

		void extendSingleQp(qp val, double * his, double * los);
		void clearVec(double * his, double * los);

		void makeQpVector(double * his, double * los, qp * result);

		int GetBlockWidth()
		{
			return _len;
		}


		~qpMath();

	private:
		int _len;
		twoSum * _twoSum;
		twoProd * _twoProd;

		double * _two;
	};

}

