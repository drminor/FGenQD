#pragma once


//#ifdef FGEN_EXPORTS
//#define FGEN_API __declspec(dllexport)
//#else
//#define FGEN_API __declspec(dllimport)
//#endif

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

		void addQps(double * ahis, double * alos, double * bhis, double * blos);

		void mulQpByD(double * his, double * los, double * f, double * rhis, double * rlos);

		void extendSingleQp(qp val, double * his, double * los);

		void makeQpVector(double * his, double * los, qp * result);


		~qpMath();

	private:
		int _len;
		twoSum * _twoSum;
		twoProd * _twoProd;
	};

}

