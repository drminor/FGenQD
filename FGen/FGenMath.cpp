#include "stdafx.h"

#include "../QPVec/vHelper.h"
#include "FGenMath.h"
#include "qpMathVec.h"

namespace FGen
{
	FGenMath::FGenMath(int len) : _qpCalc(new qpMathVec(len))
	{
		_len = len;

		_vhelper = new vHelper();
		_two = _vhelper->createAndInitVec(_len, 2.0);
		//_four = _vhelper->createAndInitVec(_len, 4.0);

	}

	FGenMath::~FGenMath()
	{
		delete _vhelper;
		delete[] _two;
		delete _qpCalc;
		_qpCalc = 0;
	}

	void FGenMath::extendSingleQp(qp val, double * his, double * los)
	{
		_qpCalc->extendSingleQp(val, his, los);
	}

	void FGenMath::Iterate(GenPt &genPt)
	{
		//   zY = 2 * zX * zY + cY;
		//zX * zY -> r
		_qpCalc->mulQpByQp(genPt._zxCordHis, genPt._zxCordLos, genPt._zyCordHis, genPt._zyCordLos, genPt._rCordHis, genPt._rCordLos);

		double zy = genPt._zxCordHis[0] * genPt._zyCordHis[0];

		//r * 2 -> zX;
		_qpCalc->mulQpByD(genPt._rCordHis, genPt._rCordLos, _two, genPt._zxCordHis, genPt._zxCordLos);
		zy *= 2;

		//zX + cY -> zY;
		_qpCalc->addQps(genPt._zxCordHis, genPt._zxCordLos, genPt._cyCordHis, genPt._cyCordLos, genPt._zyCordHis, genPt._zyCordLos);
		zy += genPt._cyCordHis[0];
		//double zyComp = genPt._zyCordHis[0];
		//genPt._zyCordHis[1] = zy;

		//  zX = xSquared - ySquared + cX;
		//xSquared - ySquared -> r
		_qpCalc->subQps(genPt._xsCordHis, genPt._xsCordLos, genPt._ysCordHis, genPt._ysCordLos, genPt._rCordHis, genPt._rCordLos);
		double zx = genPt._xsCordHis[0] - genPt._ysCordHis[0];

		//r + cX -> zX
		_qpCalc->addQps(genPt._rCordHis, genPt._rCordLos, genPt._cxCordHis, genPt._cxCordLos, genPt._zxCordHis, genPt._zxCordLos);
		zx += genPt._cxCordHis[0];
		//genPt._zxCordHis[1] = zx;
		//double zxComp = genPt._zxCordHis[0];


		//xSquared = zX * zX;
		_qpCalc->sqrQp(genPt._zxCordHis, genPt._zxCordLos, genPt._xsCordHis, genPt._xsCordLos);
		double xSq = zx * zx;
		//genPt._xsCordHis[1] = xSq;
		//double xSqComp = genPt._xsCordHis[0];

		//ySquared = zY * zY;
		_qpCalc->sqrQp(genPt._zyCordHis, genPt._zyCordLos, genPt._ysCordHis, genPt._ysCordLos);
		double ySq = zy * zy;
		//genPt._ysCordHis[1] = ySq;
		//double ySqComp = genPt._ysCordHis[0];

		//_sumSqs = xSquared + ySquared
		_qpCalc->addQps(genPt._xsCordHis, genPt._xsCordLos, genPt._ysCordHis, genPt._ysCordLos, genPt._sumSqsHis, genPt._sumSqsLos);
		double ss = xSq + ySq;
		//genPt._sumSqsHis[1] = ss;
		//double ssComp = genPt._sumSqsHis[0];

		//_sumSqsM4 = (xSquared + ySquared) - 4;
		//_qpCalc->subDFromQps(genPt._rCordHis, genPt._rCordHis, _four, genPt._sumSqsHis, genPt._sumSqsLos);
	}

}
