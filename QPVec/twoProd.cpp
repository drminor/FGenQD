
#pragma once

#include "stdafx.h"
#include <math.h>
#include "qpvec.h"

namespace qpvec
{

	//double twoProd::two_prod(double a, double b, double& err)
	//{
	//	double p = a * b;
	//	if (!isinf(p))
	//	{
	//		double a_hi, a_lo, b_hi, b_lo;

	//		split(a, a_hi, a_lo);
	//		split(b, b_hi, b_lo);

	//		err = ((a_hi * b_hi - p) + a_hi * b_lo + a_lo * b_hi) + a_lo * b_lo;
	//	}
	//	else
	//	{
	//		err = 0.0;
	//	}

	//	return p;
	//}

	void twoProd::two_prodA(double *a, double *b, double *p, double *err)
	{
		//double p = a * b;
		vdMul(_len, a, b, p);

		//double a_hi, a_lo, b_hi, b_lo;
		_vh->clearVec(_len, _a_hi);
		_vh->clearVec(_len, _a_lo);
		_vh->clearVec(_len, _b_hi);
		_vh->clearVec(_len, _b_lo);

		splitA(a, _a_hi, _a_lo);
		splitA(b, _b_hi, _b_lo);

		//err = ((a_hi * b_hi - p) + a_hi * b_lo + a_lo * b_hi) + a_lo * b_lo;

		_vh->clearVec(_len, _ah_m_bh);
		vdMul(_len, _a_hi, _b_hi, _ah_m_bh);

		_vh->clearVec(_len, _ah_m_bh_minus_p);
		vdSub(_len, _ah_m_bh, p, _ah_m_bh_minus_p);

		_vh->clearVec(_len, _ah_m_bl);
		vdMul(_len, _a_hi, _b_lo, _ah_m_bl);

		_vh->clearVec(_len, _s1);
		vdAdd(_len, _ah_m_bh_minus_p, _ah_m_bl, _s1);

		_vh->clearVec(_len, _al_m_bh);
		vdMul(_len, _a_lo, _b_hi, _al_m_bh);

		_vh->clearVec(_len, _s2);
		vdAdd(_len, _s1, _al_m_bh, _s2);

		_vh->clearVec(_len, _al_m_bl);
		vdMul(_len, _a_lo, _b_lo, _al_m_bl);

		vdAdd(_len, _s2, _al_m_bl, err);
	}

	// Multiplies the array of doubles by the single qp (hi and lo)
	// and returns an array of qp in rHis and rLos
	void twoProd::two_prod_dArrayByQp(double *a, double hi, double lo, double * rHis, double * rLos)
	{

	}



	//void twoProd::split(double a, double& hi, double& lo)
	//{
	//	//int const QD_BITS = (std::numeric_limits< double >::digits + 1) / 2;
	//	//static double const QD_SPLITTER = std::ldexp(1.0, QD_BITS) + 1.0;
	//	//static double const QD_SPLIT_THRESH = std::ldexp((std::numeric_limits< double >::max)(), -QD_BITS - 1);

	//	static double const QD_SPLITTER = pow(2, 27) + 1.0;
	//	//static double const QD_SPLIT

	//	double temp;

	//	//if (std::abs(a) > QD_SPLIT_THRESH)
	//	//{
	//	//	a = std::ldexp(a, -QD_BITS - 1);
	//	//	temp = QD_SPLITTER * a;
	//	//	hi = temp - (temp - a);
	//	//	lo = a - hi;
	//	//	hi = std::ldexp(hi, QD_BITS + 1);
	//	//	lo = std::ldexp(lo, QD_BITS + 1);
	//	//}
	//	//else
	//	//{
	//	//	temp = QD_SPLITTER * a;
	//	//	hi = temp - (temp - a);
	//	//	lo = a - hi;
	//	//}


	//	temp = QD_SPLITTER * a;
	//	hi = temp - (temp - a);
	//	lo = a - hi;
	//}

	void twoProd::splitA(double *a, double *hi, double *lo)
	{
		//temp = QD_SPLITTER * a;
		_vh->clearVec(_len, _splitTemp);
		vdMul(_len, _splitter, a, _splitTemp);

		//hi = temp - (temp - a);
		_vh->clearVec(_len, _temp_minus_a);
		vdSub(_len, _splitTemp, a, _temp_minus_a);
		vdSub(_len, _splitTemp, _temp_minus_a, hi);

		//lo = a - hi;
		vdSub(_len, a, hi, lo);
	}

	void twoProd::splitSingle(double *a, double *hi, double *lo)
	{
		//temp = QD_SPLITTER * a;
		_vh->clearVec(1, _splitTemp);
		vdMul(1, _splitter, a, _splitTemp);

		//hi = temp - (temp - a);
		_vh->clearVec(1, _temp_minus_a);
		vdSub(1, _splitTemp, a, _temp_minus_a);
		vdSub(1, _splitTemp, _temp_minus_a, hi);

		//lo = a - hi;
		vdSub(1, a, hi, lo);
	}

	twoProd::twoProd(int len)
	{
		_len = len;
		_vh = new vHelper();

		_splitter = _vh->createVec(_len);
		double splitMult = pow(2, 27) + 1.0;
		for (int i = 0; i < _len; i++)
		{
			_splitter[i] = splitMult;
		}

		_splitTemp = _vh->createVec(_len);
		_temp_minus_a = _vh->createVec(_len);

		_a_hi = _vh->createVec(_len);
		_a_lo = _vh->createVec(_len);
		_b_hi = _vh->createVec(_len);
		_b_lo = _vh->createVec(_len);

		_ah_m_bh = _vh->createVec(_len);
		_ah_m_bl = _vh->createVec(_len);
		_al_m_bh = _vh->createVec(_len);
		_al_m_bl = _vh->createVec(_len);

		_ah_m_bh_minus_p = _vh->createVec(_len);
		_s1 = _vh->createVec(_len);
		_s2 = _vh->createVec(_len);
	}

	twoProd::~twoProd()
	{
		delete _vh;
		delete[] _splitter, _splitTemp, _temp_minus_a;
		delete[] _a_hi, _a_lo, _b_hi, _b_lo;
		delete[] _ah_m_bh, _ah_m_bl, _al_m_bh, _al_m_bl;
		delete[] _ah_m_bh_minus_p, _s1, _s2;
	}
}
