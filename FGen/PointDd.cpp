#include "stdafx.h"
#include "PointDd.h"

namespace FGen
{
	PointDd::PointDd(dd_real x, dd_real y) : x(x), y(y)
	{
	}

	PointDd::PointDd()
	{
		x = 0;
		y = 0;
	}

	PointDd::~PointDd()
	{
	}
}
