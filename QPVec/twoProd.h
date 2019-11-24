#pragma once

#include "qpvec.h"
#include <math.h>

namespace qpvec
{
	class QPVEC_API twoProd
	{
	public:

		//double two_prod(double a, double b, double& err);
		void two_prodA(double *a, double *b, double *p, double *err);

		void two_prod_dArrayByQp(double * a, double hi, double lo, double * rHis, double * rLos);

		//void split(double a, double & hi, double & lo);
		void splitA(double * a, double * hi, double * lo);
		void splitSingle(double * a, double * hi, double * lo);

		twoProd(int len);
		~twoProd();

	private:
		int _len;
		vHelper * _vh;

		// For Split
		double * _splitter;
		double * _splitTemp;
		double * _temp_minus_a;

		// For TwoProd
		double * _a_hi;
		double * _a_lo;
		double * _b_hi;
		double * _b_lo;

		double * _ah_m_bh;
		double * _ah_m_bl;
		double * _al_m_bh;
		double *_al_m_bl;

		double * _ah_m_bh_minus_p;
		double * _s1;
		double * _s2;
	};
}
