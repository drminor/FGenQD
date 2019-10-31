#include "stdafx.h"
#include "CoordsDd.h"
#include "PointDd.h"

namespace FGen
{
	CoordsDd::CoordsDd()
	{
		start = PointDd(0, 0);
		end = PointDd(0, 0);
	}

	CoordsDd::CoordsDd(PointDd start, PointDd end) : start(start), end(end)
	{
	}

	CoordsDd::~CoordsDd()
	{
	}
}
