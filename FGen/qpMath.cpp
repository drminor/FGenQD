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

	void qpMath::addQps(double * ahis, double * alos, double * bhis, double * blos, double * rhis, double * rlos)
	{
		double * e1 = new double[_len];

		double * t1 = new double[_len];
		double * e2 = new double[_len];

		double * e3 = new double[_len];

		for (int i = 0; i < _len; i++) {
			e1[i] = 0.0;

			t1[i] = 0.0;
			e2[i] = 0.0;
			e3[i] = 0.0;
		}

		_twoSum->two_sumA(ahis, bhis, rhis, e1);

		_twoSum->two_sumA(alos, blos, t1, e2);
		_twoSum->two_sumA(e1, t1, rlos, e3);

		vdAdd(_len, e2, e3, e1);

		_twoSum->three_sum2(rhis, rlos, e1);

		delete[] e1, t1, e2, e3;

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
	}

	void qpMath::subQps(double * ahis, double * alos, double * bhis, double * blos, double * rhis, double * rlos)
	{
		double * e1 = new double[_len];

		double * t1 = new double[_len];
		double * e2 = new double[_len];

		double * e3 = new double[_len];

		for (int i = 0; i < _len; i++) {
			e1[i] = 0.0;

			t1[i] = 0.0;
			e2[i] = 0.0;
			e3[i] = 0.0;
		}

		_twoSum->two_diffA(ahis, bhis, rhis, e1);

		_twoSum->two_diffA(alos, blos, t1, e2);
		_twoSum->two_sumA(e1, t1, rlos, e3);

		vdAdd(_len, e2, e3, e1);

		_twoSum->three_sum2(rhis, rlos, e1);

		delete[] e1, t1, e2, e3;

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

	void qpMath::subDFromQps(double * ahis, double * alos, double * b, double * rhis, double * rlos)
	{
		double * e1 = new double[_len];
		double * e2 = new double[_len];

		for (int i = 0; i < _len; i++) {
			e1[i] = 0.0;
			e2[i] = 0.0;
		}

		_twoSum->two_diffA(ahis, b, rhis, e1);

		_twoSum->two_sumA(alos, e1, rlos, e2);
		_twoSum->three_sum2(rhis, rlos, e2);

		//dd_real& operator-=(double b)
		//{
		//	double s2;
		//	x[0] = qd::two_sum(x[0], -b, s2);
		//	if (QD_ISFINITE(x[0]))
		//	{
		//		x[1] = qd::two_sum(x[1], s2, s2);
		//		qd::three_sum(x[0], x[1], s2);
		//	}
		//	else
		//	{
		//		x[1] = 0.0;
		//	}
		//	return *this;
		//}
	}

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

	}

	void qpMath::mulQpByQp(double * ahis, double * alos, double * bhis, double * blos, double * rhis, double * rlos)
	{
		double * m2 = new double[_len];
		double * m3 = new double[_len];
		double * m4 = new double[_len];
		double * m5 = new double[_len];
		double * m6 = new double[_len];

		for (int i = 0; i < _len; i++) {
			m2[i] = 0.0;
			m3[i] = 0.0;
			m4[i] = 0.0;
			m5[i] = 0.0;
			m6[i] = 0.0;
		}

		//p[0] = qd::two_prod(x[0], b.x[0], p[1]);
		_twoProd->two_prodA(ahis, bhis, rhis, rlos);

		//p[2] = qd::two_prod(x[0], b.x[1], p[4]);
		_twoProd->two_prodA(ahis, blos, m2, m4);

		//p[3] = qd::two_prod(x[1], b.x[0], p[5]);
		_twoProd->two_prodA(alos, bhis, m3, m5);

		//p[6] = x[1] * b.x[1];
		vdMul(_len, alos, blos, m6);

		//	e powers in p = 0, 1, 2, 3, 2, 2, 2
		//qd::three_sum(p[1], p[2], p[3]);
		_twoSum->three_sum2(rlos, m2, m3);

		//	e powers in p = 0, 1, 2, 3, 2, 3, 4
		//p[2] += p[4] + p[5] + p[6];
		vdAdd(_len, m2, m4, m3);
		vdAdd(_len, m3, m5, m4);
		vdAdd(_len, m4, m6, m5);

		//qd::three_sum(p[0], p[1], p[2]);
		_twoSum->three_sum2(rhis, rlos, m5);

		//dd_real& operator*=(dd_real const& b)
		//{
		//	double p[7];
		//	//	e powers in p = 0, 1, 1, 1, 2, 2, 2
		//	p[0] = qd::two_prod(x[0], b.x[0], p[1]);
		//	if (QD_ISFINITE(p[0]))
		//	{
		//		p[2] = qd::two_prod(x[0], b.x[1], p[4]);
		//		p[3] = qd::two_prod(x[1], b.x[0], p[5]);
		//		p[6] = x[1] * b.x[1];

		//		//	e powers in p = 0, 1, 2, 3, 2, 2, 2
		//		qd::three_sum(p[1], p[2], p[3]);

		//		//	e powers in p = 0, 1, 2, 3, 2, 3, 4
		//		p[2] += p[4] + p[5] + p[6];

		//		qd::three_sum(p[0], p[1], p[2]);

		//		x[0] = p[0];
		//		x[1] = p[1];
		//	}
		//	else
		//	{
		//		x[0] = p[0];
		//		x[1] = 0.0;
		//	}
		//	return *this;
		//}
	}

	void qpMath::sqrQp(double * ahis, double * alos, double * rhis, double * rlos)
	{
		double * p1 = new double[_len];
		double * p2 = new double[_len];
		double * p3 = new double[_len];
		double * p4 = new double[_len];

		for (int i = 0; i < _len; i++) {
			p1[i] = 0.0;
			p2[i] = 0.0;
			p3[i] = 0.0;
			p4[i] = 0.0;
		}

		_twoProd->two_sqrA(ahis, p1, p2);
		vdMul(_len, ahis, alos, p3);
		vdMul(_len, p3, _twoProd->_two, p4);

		vdAdd(_len, p2, p4, p3);

		vdMul(_len, alos, alos, p2);
		vdAdd(_len, p3, p2, p4);

		_twoSum->quick_two_sumA(p1, p4, rhis, rlos);


		//dd_real sqr(dd_real const& a)
		//{
		//	if (std::isnan(a))
		//		return a;

		//	double p2, p1 = qd::two_sqr(a._hi(), p2);
		//	p2 += 2.0 * a._hi() * a._lo();
		//	p2 += a._lo() * a._lo();

		//	double s2, s1 = qd::quick_two_sum(p1, p2, s2);
		//	return dd_real(s1, s2);
		//}
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
