#include "stdafx.h"

#include "../QPVec/vHelper.h"
#include "FGenMath.h"
#include "qpMath.h"

namespace FGen
{
	FGenMath::FGenMath(int len) : _qpCalc(new qpMath(len))
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
		_qpCalc->mulQpByQp(genPt._zxCordHis, genPt._zxCordLos, genPt._zyCordHis, genPt._zyCordLos, genPt._rCordHis, genPt._rCordHis);

		//r * 2 -> zX;
		_qpCalc->mulQpByD(genPt._rCordHis, genPt._rCordLos, _two, genPt._zxCordHis, genPt._zxCordLos);

		//zX + cY -> zY;
		_qpCalc->addQps(genPt._zxCordHis, genPt._zxCordLos, genPt._cyCordHis, genPt._cyCordLos, genPt._zyCordHis, genPt._zyCordLos);


		//  zX = xSquared - ySquared + cX;
		//xSquared - ySquared -> r
		_qpCalc->subQps(genPt._xsCordHis, genPt._xsCordLos, genPt._ysCordHis, genPt._ysCordLos, genPt._rCordHis, genPt._rCordLos);

		//r + cX -> zX
		_qpCalc->addQps(genPt._rCordHis, genPt._rCordLos, genPt._cxCordHis, genPt._cxCordLos, genPt._zxCordHis, genPt._zxCordLos);


		//xSquared = zX * zX;
		_qpCalc->sqrQp(genPt._zxCordHis, genPt._zxCordLos, genPt._xsCordHis, genPt._xsCordLos);

		//ySquared = zY * zY;
		_qpCalc->sqrQp(genPt._zyCordHis, genPt._zyCordLos, genPt._ysCordHis, genPt._ysCordLos);

		//_sumSqs = xSquared + ySquared
		_qpCalc->addQps(genPt._xsCordHis, genPt._xsCordLos, genPt._ysCordHis, genPt._ysCordLos, genPt._sumSqsHis, genPt._sumSqsLos);

		//_sumSqsM4 = (xSquared + ySquared) - 4;
		//_qpCalc->subDFromQps(genPt._rCordHis, genPt._rCordHis, _four, genPt._sumSqsHis, genPt._sumSqsLos);
	}

}
