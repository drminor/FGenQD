#include "stdafx.h"
#include "GenPt.h"


namespace FGen
{
	GenPt::GenPt(int blockWidth, double * cxCordHis, double * cxCordLos, double * cyCordHis, double * cyCordLos)
	{
		_blockWidth = blockWidth;

		_cnt = new int[blockWidth];

		_cxCordHis = cxCordHis;
		_cxCordLos = cxCordLos;
		_cyCordHis = cyCordHis;
		_cyCordLos = cyCordLos;

		_resultIndexes = new PointInt[blockWidth];

		_zxCordHis = new double[blockWidth];
		_zxCordLos = new double[blockWidth];
		_zyCordHis = new double[blockWidth];
		_zyCordLos = new double[blockWidth];

		_xsCordHis = new double[blockWidth];
		_xsCordLos = new double[blockWidth];
		_ysCordHis = new double[blockWidth];
		_ysCordLos = new double[blockWidth];

		_sumSqsHis = new double[blockWidth];
		_sumSqsLos = new double[blockWidth];

		_rCordHis = new double[blockWidth];
		_rCordLos = new double[blockWidth];


		for (int i = 0; i < blockWidth; i++) {
			_cnt[i] = 0;

			_zxCordHis[i] = 0;
			_zxCordLos[i] = 0;
			_zyCordHis[i] = 0;
			_zyCordLos[i] = 0;

			_xsCordHis[i] = 0;
			_xsCordLos[i] = 0;
			_ysCordHis[i] = 0;
			_ysCordLos[i] = 0;

			_sumSqsHis[i] = 0;
			_sumSqsLos[i] - 0;
			_resultIndexes[i] = PointInt(i, 0);

			_rCordHis[i] = 0;
			_rCordLos[i] = 0;
		}
	}

	void GenPt::SetC(qp x, qp y, int index, PointInt & resultIndex)
	{
		_cxCordHis[index] = x._hi();
		_cxCordLos[index] = x._lo();
		_cyCordHis[index] = y._hi();
		_cyCordLos[index] = y._lo();
		Clear(index);
	}

	void GenPt::SetCX(qp val, int index, PointInt & resultIndex)
	{
		_cxCordHis[index] = val._hi();
		_cxCordLos[index] = val._lo();
		_resultIndexes[index] = resultIndex;
		Clear(index);
	}

	void GenPt::Clear(int index)
	{
		_cnt[index] = 0;

		_zxCordHis[index] = 0;
		_zxCordLos[index] = 0;
		_zyCordHis[index] = 0;
		_zyCordLos[index] = 0;

		_xsCordHis[index] = 0;
		_xsCordLos[index] = 0;
		_ysCordHis[index] = 0;
		_ysCordLos[index] = 0;

		_sumSqsHis[index] = 0;
		_sumSqsLos[index] = 0;
	}

	void GenPt::SetEmpty(int index)
	{
		_resultIndexes[index] = PointInt(-1,-1);
	}

	bool GenPt::IsEmpty(int index)
	{
		return _resultIndexes[index].X() == -1;
	}	

	GenPt::~GenPt()
	{
		delete[] _zxCordHis, _zxCordLos, _zyCordHis, _zyCordLos;
		delete[] _xsCordHis, _xsCordLos, _ysCordHis, _ysCordLos;
		delete[] _cnt, _resultIndexes, _sumSqsHis, _sumSqsLos;

		delete[] _rCordHis, _rCordLos;

	}
}
