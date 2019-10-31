#pragma once

#include <qd/dd_real.h>
#include "PointDd.h"

namespace FGen
{
	struct CoordsDd
	{
	public:

		CoordsDd();
		CoordsDd(PointDd start, PointDd end);

		inline PointDd Start() const
		{
			return start;
		};

		inline PointDd End() const
		{
			return end;
		};

		inline dd_real SX() const
		{
			return start.X();
		};

		inline dd_real EX() const
		{
			return end.X();
		};

		inline dd_real SY() const
		{
			return start.Y();
		};

		inline dd_real EY() const
		{
			return end.Y();
		};

		inline dd_real Width() const
		{
			return end.X() - start.X();
		};

		inline dd_real Height() const
		{
			return end.Y() - start.Y();
		};


		~CoordsDd();

	private:
		PointDd start;
		PointDd end;

	};

}

