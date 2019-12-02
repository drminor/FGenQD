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
		initWorkingVectors();
	}

	qpMath::qpMath(int len)
	{
		_len = len;
		initWorkingVectors();
	}

	void qpMath::initWorkingVectors()
	{
		_twoSum = new twoSum(_len);
		_twoProd = new twoProd(_len);

		_t1 = new double[_len];

		_e1 = new double[_len];
		_e2 = new double[_len];
		_e3 = new double[_len];

		_p1 = new double[_len];
		_p2 = new double[_len];
		_p3 = new double[_len];

		//for (int i = 0; i < _len; i++) {
		//	_t1[i] = 0.0;

		//	_e1[i] = 0.0;
		//	_e2[i] = 0.0;
		//	_e3[i] = 0.0;

		//	_p1[i] = 0.0;
		//	_p2[i] = 0.0;
		//	_p3[i] = 0.0;
		//}
	}

	qpMath::~qpMath()
	{
		delete _twoSum;
		delete _twoProd;
		delete[] _t1, _e1, _e2, _e3, _p1, _p2, _p3;
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
		_twoSum->two_sumA(ahis, bhis, rhis, _e1);

		_twoSum->two_sumA(alos, blos, _t1, _e2);
		_twoSum->two_sumA(_e1, _t1, rlos, _e3);

		vdAdd(_len, _e2, _e3, _e1);

		_twoSum->three_sum2(rhis, rlos, _e1);


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
		_twoSum->two_diffA(ahis, bhis, rhis, _e1);

		_twoSum->two_diffA(alos, blos, _t1, _e2);
		_twoSum->two_sumA(_e1, _t1, rlos, _e3);

		vdAdd(_len, _e2, _e3, _e1);

		_twoSum->three_sum2(rhis, rlos, _e1);

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
		_twoSum->two_diffA(ahis, b, rhis, _e1);

		_twoSum->two_sumA(alos, _e1, rlos, _e2);
		_twoSum->three_sum2(rhis, rlos, _e2);

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
		_twoProd->two_prodA(his, f, rhis, _p1);
		vdMul(_len, los, f, rlos);

		_twoSum->three_sum2(rhis, rlos, _p1);

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
		//p[0] = qd::two_prod(x[0], b.x[0], p[1]);
		_twoProd->two_prodA(ahis, bhis, rhis, rlos);

		//p[2] = qd::two_prod(x[0], b.x[1], p[4]);
		_twoProd->two_prodA(ahis, blos, _p1, _e1);

		//p[3] = qd::two_prod(x[1], b.x[0], p[5]);
		_twoProd->two_prodA(alos, bhis, _p2, _e2);

		//p[6] = x[1] * b.x[1];
		vdMul(_len, alos, blos, _e3);

		//	e powers in p = 0, 1, 2, 3, 2, 2, 2
		//qd::three_sum(p[1], p[2], p[3]);
		_twoSum->three_sum2(rlos, _p1, _p2);

		//	e powers in p = 0, 1, 2, 3, 2, 3, 4
		//p[2] += p[4] + p[5] + p[6];
		vdAdd(_len, _p1, _e1, _p2);
		vdAdd(_len, _p2, _e2, _e1);
		vdAdd(_len, _e1, _e3, _e2);

		//qd::three_sum(p[0], p[1], p[2]);
		_twoSum->three_sum2(rhis, rlos, _e2);

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
		_twoProd->two_sqrA(ahis, _p1, _e1);
		vdMul(_len, ahis, alos, _p2);
		vdMul(_len, _p2, _twoProd->_two, _p3);

		vdAdd(_len, _e1, _p3, _p2);

		vdMul(_len, alos, alos, _e1);
		vdAdd(_len, _p2, _e1, _p3);

		_twoSum->quick_two_sumA(_p1, _p3, rhis, rlos);

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

	// quad-double = double-double * double-double
	void qpMath::mulQpByQpROp(double ahi, double alo, double bhi, double blo, double * r)
	{
		if (_len != 1) {
			throw std::invalid_argument("mulQpByQpROp must only be called on instances constructed with Len = 1.");
		}

		double p4, p5, p6, p7, t1, t2;

		//	powers of e - 0, 1, 1, 1, 2, 2, 2, 3
		//	p[0] = qd::two_prod(a._hi(), b._hi(), p[1]);
		_twoProd->two_prodA(&ahi, &bhi, &r[0], &r[1]);

		//	if (QD_ISFINITE(p[0]))
		//	{
		if(_finite(r[0]) != 0)
		{
			//	p[2] = qd::two_prod(a._hi(), b._lo(), p4);
			_twoProd->two_prodA(&ahi, &blo, &r[2], &p4);

			//	p[3] = qd::two_prod(a._lo(), b._hi(), p5);
			_twoProd->two_prodA(&alo, &bhi, &r[3], &p5);

			//	p6 = qd::two_prod(a._lo(), b._lo(), p7);
			_twoProd->two_prodA(&alo, &blo, &p6, &p7);

			//	powers of e - 0, 1, 2, 3, 2, 2, 2, 3
			//	qd::three_sum(p[1], p[2], p[3]);
			_twoSum->three_sum(&r[1], &r[2], &r[3]);

			//	powers of e - 0, 1, 2, 3, 2, 3, 4, 3
			//	qd::three_sum(p4, p5, p6);
			_twoSum->three_sum(&p4, &p5, &p6);

			//	powers of e - 0, 1, 2, 3, 3, 3, 4, 3
			//	p[2] = qd::two_sum(p[2], p4, p4);
			_twoSum->quick_two_sumA(&r[2], &p4, &t1, &t2);
			r[2] = t1;
			p4 = t2;

			//	powers of e - 0, 1, 2, 3, 4, 5, 4, 3
			//	qd::three_sum(p[3], p4, p5);
			_twoSum->three_sum(&r[3], &p4, &p5);

			//	powers of e - 0, 1, 2, 3, 4, 5, 4, 4
			//	p[3] = qd::two_sum(p[3], p7, p7);
			_twoSum->quick_two_sumA(&r[3], &p7, &t1, &t2);
			r[3] = t1;
			p7 = t2;

			p4 += (p6 + p7);

			renorm(r[0], r[1], r[2], r[3], p4);
		}
		else
		{
			r[1] = r[2] = r[3] = 0.0;
		}
	}

	// quad-double + double-double
	void qpMath::addOpAndQp(double const* a, double bhi, double blo, double * s)
	{
		if (_len != 1) {
			throw std::invalid_argument("addOpAndQp must only be called on instances constructed with Len = 1.");
		}

		double * f = new double[4];
		for (int i = 0; i < 4; i++) {
			f[i] = a[i];
		}

		//	double t[5];
		double t0, t1, t2, t3;

		//	s[0] = qd::two_sum(a[0], b._hi(), t[0]);		//	s0 - O( 1 ); t0 - O( e )
		_twoSum->quick_two_sumA(&f[0], &bhi, &s[0], &t0);

		//	s[1] = qd::two_sum(a[1], b._lo(), t[1]);		//	s1 - O( e ); t1 - O( e^2 )
		_twoSum->quick_two_sumA(&f[1], &blo, &s[1], &t1);

		//	s[1] = qd::two_sum(s[1], t[0], t[0]);			//	s1 - O( e ); t0 - O( e^2 )
		_twoSum->quick_two_sumA(&s[1], &t0, &t2, &t3);
		s[1] = t2;
		t0 = t3;

		//	s[2] = a[2];									//	s2 - O( e^2 )
		s[2] = a[2];

		//	qd::three_sum(s[2], t[0], t[1]);				//	s2 - O( e^2 ); t0 - O( e^3 ); t1 = O( e^4 )
		_twoSum->three_sum(&s[2], &t0, &t1);

		//	s[3] = qd::two_sum(a[3], t[0], t[0]);			//	s3 - O( e^3 ); t0 - O( e^4 )
		_twoSum->quick_two_sumA(&f[3], &t0, &s[3], &t3);

		//	t[0] += t[1];									//	fl( t0 + t1 ) - accuracy less important
		t3 += t1;

		renorm(s[0], s[1], s[2], s[3], t3);

		delete[] f;
	}

	void qpMath::renorm(double &c0, double &c1, double &c2, double &c3, double &c4)
	{
		//if (QD_ISINF(c0)) return;
		if (_finite(c0) != 0) return;

		double s0, s1, s2 = 0.0, s3 = 0.0;
		double t, e4;

		//s0 = quick_two_sum(c3, c4, c4);
		_twoSum->quick_two_sumA(&c3, &c4, &t, &e4);
		c4 = e4;

		//s0 = quick_two_sum(c2, s0, c3);
		_twoSum->quick_two_sumA(&c2, &t, &s0, &c3);

		//s0 = quick_two_sum(c1, s0, c2);
		_twoSum->quick_two_sumA(&c1, &s0, &t, &c2);

		//c0 = quick_two_sum(c0, s0, c1);
		_twoSum->quick_two_sumA(&c0, &t, &s0, &c1);
		c0 = s0;

		//s0 = c0;
		//s1 = c1;

		//s0 = quick_two_sum(c0, c1, s1);
		_twoSum->quick_two_sumA(&c0, &c1, &s0, &s1);

		if (s1 != 0.0)
		{
			//	s1 = quick_two_sum(s1, c2, s2);
			_twoSum->quick_two_sumA(&s1, &c2, &t, &s2);
			s1 = t;
			if (s2 != 0.0)
			{
				//	s2 = quick_two_sum(s2, c3, s3);
				_twoSum->quick_two_sumA(&s2, &c3, &t, &s3);
				s2 = t;
				if (s3 != 0.0)
					s3 += c4;
				else
					s2 += c4;
			}
			else
			{
				//	s1 = quick_two_sum(s1, c3, s2);
				_twoSum->quick_two_sumA(&s1, &c3, &t, &s2);
				s1 = t;

				if (s2 != 0.0)
				{
					//	s2 = quick_two_sum(s2, c4, s3);
					_twoSum->quick_two_sumA(&s2, &c4, &t, &s3);
					s2 = t;
				}
				else
				{
					//	s1 = quick_two_sum(s1, c4, s2);
					_twoSum->quick_two_sumA(&s1, &c4, &t, &s2);
					s1 = t;
				}
			}
		}
		else
		{
			//	s0 = quick_two_sum(s0, c2, s1);
			_twoSum->quick_two_sumA(&s0, &c2, &t, &s1);
			s0 = t;

			if (s1 != 0.0)
			{
				//	s1 = quick_two_sum(s1, c3, s2);
				if (s2 != 0.0)
				{
					//	s2 = quick_two_sum(s2, c4, s3);
					_twoSum->quick_two_sumA(&s2, &c4, &t, &s3);
					s2 = t;
				}
				else
				{
					//	s1 = quick_two_sum(s1, c4, s2);
					_twoSum->quick_two_sumA(&s1, &c4, &t, &s2);
					s1 = t;
				}
			}
			else
			{
				//	s0 = quick_two_sum(s0, c3, s1);
				_twoSum->quick_two_sumA(&s0, &c3, &t, &s1);
				s0 = t;

				if (s1 != 0.0)
				{
					//	s1 = quick_two_sum(s1, c4, s2);
					_twoSum->quick_two_sumA(&s1, &c4, &t, &s2);
					s1 = t;
				}
				else
				{
					//	s0 = quick_two_sum(s0, c4, s1);
					_twoSum->quick_two_sumA(&s0, &c4, &t, &s1);
					s0 = t;
				}
			}
		}

		c0 = s0;
		c1 = s1;
		c2 = s2;
		c3 = s3;
	}

	void qpMath::two_sum(double a, double b, double &s, double &err)
	{
		if (_len != 1) {
			throw std::invalid_argument("two_sum must only be called on instances constructed with Len = 1.");
		}

		_twoSum->quick_two_sumA(&a, &b, &s, &err);
	}

	void qpMath::three_sum2(double &a, double &b, double c)
	{
		if (_len != 1) {
			throw std::invalid_argument("three_sum2 must only be called on instances constructed with Len = 1.");
		}

		_twoSum->three_sum2(&a, &b, &c);
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

	void qpMath::fillQpVector(double * his, double * los, qp * result)
	{
		for (int i = 0; i < _len; i++) {
			result[i] = qp(his[i], los[i]);
		}
	}

}
