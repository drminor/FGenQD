#pragma once

#include "../QPVec/vHelper.h"
#include "qp.h"
#include "GenPt.h"

namespace FGen
{
	class qpMath;

	class FGenMath
	{
	public:
		FGenMath(int len);
		~FGenMath();

		void Iterate(GenPt &genPt);

		void extendSingleQp(qp val, double * his, double * los);


	private:
		int _len;
		qpvec::vHelper * _vhelper;
		qpMath * _qpCalc;

		double * _two;
		//double * _four;
	};
}


