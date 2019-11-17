#pragma once

#include "qpvec.h"

namespace qpvec
{
	class QPVEC_API twoSum
	{

	public:

		double two_sum(double a, double b, double & err);
		void two_sumA(double * a, double * b, double * s, double * err);

		twoSum(int len);
		~twoSum();

	private:
		int _len;
		vHelper * _vh;

		double * _bb;
		double * _b_minus_bb;
		double * _s_minus_bb;
		double * _a_minus_s_minus_bb;
	};
}
