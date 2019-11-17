#pragma once

#include "stdafx.h"
#include "twoSum.h"
#include "mkl.h"

namespace qpvec
{

	double twoSum::two_sum(double a, double b, double& err)
	{
		//double s = a + b;
		//if (QD_ISFINITE(s))
		//{
		//	double bb = s - a;
		//	err = (a - (s - bb)) + (b - bb);
		//}
		//else
		//	err = 0;
		//return s;

		double s = a + b;

		double bb = s - a;
		double bbb = b - bb;
		double sbb = s - bb;

		double asbb = a - sbb;

		double err2 = asbb + bbb;

		err = (a - (s - bb)) + (b - bb);
		return s;
	}

	void twoSum::two_sumA(double *a, double *b, double *s, double* err)
	{
		//double s = a + b;
		vdadd(&_len, a, b, s);

		//double bb = s - a;
		_vh->clearVec(_len, _bb);
		vdsub(&_len, s, a, _bb);

		//double bbb = b - bb;
		_vh->clearVec(_len, _b_minus_bb);
		vdsub(&_len, b, _bb, _b_minus_bb);

		//double sbb = s - bb;
		_vh->clearVec(_len, _s_minus_bb);
		vdsub(&_len, s, _bb, _s_minus_bb);

		//double asbb = a - sbb;
		_vh->clearVec(_len, _a_minus_s_minus_bb);
		vdsub(&_len, a, _s_minus_bb, _a_minus_s_minus_bb);

		//double err2 = asbb + bbb;
		vdadd(&_len, _a_minus_s_minus_bb, _b_minus_bb, err);

		//err = (a - (s - bb)) + (b - bb);
		//return s;
	}

	twoSum::twoSum(int len)
	{
		_len = len;
		_vh = new vHelper();

		_bb = _vh->createVec(_len);
		_b_minus_bb = _vh->createVec(_len);
		_s_minus_bb = _vh->createVec(_len);
		_a_minus_s_minus_bb = _vh->createVec(_len);
	}

	twoSum::~twoSum()
	{
		delete _vh;
		delete[] _bb, _b_minus_bb, _s_minus_bb, _a_minus_s_minus_bb;
	}
}