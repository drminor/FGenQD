#pragma once

#include "stdafx.h"
#include <vector>
#include "Job.h"
#include "qp.h"
#include "PointInt.h"

namespace FGen
{
	class GenPt
	{

	public:
		GenPt(int blockWidth, double * cxCordHis, double * cxCordLos, double * cyCordHis, double * cyCordLos);

		~GenPt();

		void SetC(qp x, qp y, int index, PointInt & resultIndex);
		void SetCX(qp val, int index, PointInt & resultIndex);
		void Clear(int index);
		void SetEmpty(int index);
		bool IsEmpty(int index);

		int _blockWidth;

		PointInt * _resultIndexes;

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

		double * _sumSqsHis;
		double * _sumSqsLos;

		int * _cnt;

		double * _rCordHis;
		double * _rCordLos;

	};


}

