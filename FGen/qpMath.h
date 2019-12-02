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

		void mulQpByQpROp(double ahi, double alo, double bhi, double blo, double * r);
		void addOpAndQp(double const* a, double bhi, double blo, double * s);
		void renorm(double &c0, double &c1, double &c2, double &c3, double &c4);

		void two_sum(double a, double b, double &s, double &err);
		void three_sum2(double &a, double &b, double c);

		void extendSingleQp(qp val, double * his, double * los);
		void clearVec(double * his, double * los);

		void fillQpVector(double * his, double * los, qp * result);

		int GetBlockWidth()
		{
			return _len;
		}


		~qpMath();

	private:
		int _len;
		twoSum * _twoSum;
		twoProd * _twoProd;

		double * _t1;

		double * _e1;
		double * _e2;
		double * _e3;

		double * _p1;
		double * _p2;
		double * _p3;
		double * _two;

		void initWorkingVectors();

	};

}

