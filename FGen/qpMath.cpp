#pragma once

#include "stdafx.h"
#include "qpMath.h"
#include "../QPVec/qpvec.h"

using namespace qpvec;

namespace FGen
{
	qpMath::qpMath()
	{
		_len = 1;
		_twoSum = new twoSum(1);
		_twoProd = new twoProd(1);
	}

	qpMath::qpMath(int len)
	{
		_len = len;
		_twoSum = new twoSum(_len);
		_twoProd = new twoProd(_len);
	}

	qpMath::~qpMath()
	{
		delete _twoSum;
		delete _twoProd;
	}

	qp qpMath::getDiff(qp end, qp start)
	{
		if (_len != 1) {
			throw std::invalid_argument("getDiff must only be called on instances constructed with Len = 1.");
		}

		double aHi = end._hi();
		double aLo = end._lo();

		double bHi = start._hi();
		double bLo = start._lo();

		double s1 = 0.0;
		double s2 = 0.0;

		_twoSum->two_diffA(&aHi, &bHi, &s1, &s2);

		double t1 = 0.0;
		double t2 = 0.0;
		double t3 = 0.0;

		_twoSum->two_diffA(&aLo, &bLo, &t1, &t2);
		_twoSum->two_sumA(&s2, &t1, &aLo, &t3);

		t3 += t2;
		_twoSum->three_sum(&s1, &aLo, &t3);
		return qp(s1, aLo);

		//dd_real& operator-=(dd_real const& b)
		//{
		//	double s2;
		//	x[0] = qd::two_sum(x[0], -b.x[0], s2);
		//	if (QD_ISFINITE(x[0]))
		//	{
		//		double t2, t1 = qd::two_sum(x[1], -b.x[1], t2);
		//		x[1] = qd::two_sum(s2, t1, t1);
		//		t1 += t2;
		//		qd::three_sum(x[0], x[1], t1);
		//	}
		//	else
		//	{
		//		x[1] = 0.0;
		//	}
		//	return *this;
		//}

	}

	//dd_real& operator+=(dd_real const& b)
//{
//	double s2;
//	x[0] = qd::two_sum(x[0], b.x[0], e1);
//	if (QD_ISFINITE(x[0]))
//	{
//		double t2, t1 = qd::two_sum(x[1], b.x[1], e2);
//		x[1] = qd::two_sum(e1, t1, e3);
//		e3 += e2;
//		qd::three_sum(x[0], x[1], e3);
//	}
//	else
//	{
//		x[1] = 0.0;
//	}
//	return *this;
//}

	// Adds (in place) qp B to qp A
	void qpMath::addQps(double * ahis, double * alos, double * bhis, double * blos)
	{
		double * s1 = new double[_len];
		double * e1 = new double[_len];

		double * t1 = new double[_len];
		double * e2 = new double[_len];

		double * e3 = new double[_len];

		for (int i = 0; i < _len; i++) {
			s1[i] = 0.0;
			e1[i] = 0.0;

			t1[i] = 0.0;
			e2[i] = 0.0;
			e3[i] = 0.0;
		}

		_twoSum->two_sumA(ahis, bhis, s1, e1);
		for (int i = 0; i < _len; i++) {
			ahis[i] = s1[i];
		}

		_twoSum->two_sumA(alos, blos, t1, e2);
		_twoSum->two_sumA(e1, t1, alos, e3);

		vdAdd(_len, e2, e3, e1);

		_twoSum->three_sum2(ahis, alos, e1);

		delete[] s1, e1, t1, e2, e3;
	}

	//dd_real& operator*=(double b)
//{
//	double p1;
//	x[0] = qd::two_prod(x[0], b, p1);
//	if (QD_ISFINITE(x[0]))
//	{
//		x[1] *= b;
//		qd::three_sum(x[0], x[1], p1);
//	}
//	else
//	{
//		x[1] = 0.0;
//	}
//	return *this;
//}
	void qpMath::mulQpByD(double * his, double * los, double * f, double * rhis, double * rlos)
	{
		double * p1 = new double[_len];

		for (int i = 0; i < _len; i++) {
			p1[i] = 0.0;
		}

		_twoProd->two_prodA(his, f, rhis, p1);
		vdMul(_len, los, f, rlos);

		_twoSum->three_sum2(rhis, rlos, p1);

		delete p1;
	}

	void qpMath::extendSingleQp(qp val, double * his, double * los)
	{
		double hi = val._hi();
		double lo = val._lo();

		for (int i = 0; i < _len; i++) {
			his[i] = hi;
			los[i] = lo;
		}
	}

	void qpMath::clearVec(double * his, double * los)
	{
		for (int i = 0; i < _len; i++) {
			his[i] = 0.0;
			los[i] = 0.0;
		}
	}

	void qpMath::makeQpVector(double * his, double * los, qp * result)
	{
		for (int i = 0; i < _len; i++) {
			result[i] = qp(his[i], los[i]);
		}
	}

}
