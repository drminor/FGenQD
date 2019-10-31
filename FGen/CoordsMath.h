#pragma once

#include <qd/dd_real.h>
#include "CoordsDd.h"
#include "PointDd.h"
#include "SizeInt.h"
#include "PointInt.h"
#include "RectangleInt.h"

namespace FGen
{
	class CoordsMath
	{
	public:

		CoordsMath();

		CoordsDd ZoomIn(CoordsDd coords, SizeInt samplePoints, RectangleInt area);
		CoordsDd ZoomOut(CoordsDd coords, double amount);

		CoordsDd ShiftRight(CoordsDd coords, double amount);
		CoordsDd ShiftUp(CoordsDd coords, double amount);

		~CoordsMath();

	private:
		dd_real GetNewCoord(dd_real vSt, int avStart, dd_real extentY, int h);
	};
}

