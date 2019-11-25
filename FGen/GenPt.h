#pragma once

#include "stdafx.h"
#include <vector>
#include "Job.h"
#include "qp.h"
#include "qpMath.h"

namespace FGen
{
	class GenPt
	{

	public:
		GenPt(qpMath * qpCalc, int blockWidth);

		~GenPt();

	private:
		int _blockWidth;
		qpMath * _qpCalc;

		double * _cxCordHis;
		double * _cxCordLos;
		double * _cyCordHis;
		double * _cyCordLos;

		double * _zxCordHis;
		double * _zxCordLos;
		double * _zyCordHis;
		double * _zyCordLos;

		double * _xsCordHis;
		double * _xsCordLos;
		double * _ysCordHis;
		double * _ysCordLos;
	};


}

