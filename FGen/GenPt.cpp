#include "stdafx.h"
#include "GenPt.h"


namespace FGen
{

	GenPt::GenPt(qpMath * qpCalc, int blockWidth)
	{
		_qpCalc = qpCalc;
		_blockWidth = blockWidth;

		_cxCordHis = new double[blockWidth];
		_cxCordLos = new double[blockWidth];
		_cyCordHis = new double[blockWidth];
		_cyCordLos = new double[blockWidth];

		_zxCordHis = new double[blockWidth];
		_zxCordLos = new double[blockWidth];
		_zyCordHis = new double[blockWidth];
		_zyCordLos = new double[blockWidth];

		_xsCordHis = new double[blockWidth];
		_xsCordLos = new double[blockWidth];
		_ysCordHis = new double[blockWidth];
		_ysCordLos = new double[blockWidth];

	}

	GenPt::~GenPt()
	{
		delete _qpCalc;
		delete[] _cxCordHis, _cxCordLos, _cyCordHis, _cyCordLos;
		delete[] _zxCordHis, _zxCordLos, _zyCordHis, _zyCordLos;
		delete[] _xsCordHis, _xsCordLos, _ysCordHis, _ysCordLos;
	}
}
