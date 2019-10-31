#pragma once

#include <qd/dd_real.h>
namespace FGen
{
	struct PointDd
	{

	public:
		PointDd();
		PointDd(dd_real x, dd_real y);

		inline dd_real X() const
		{
			return x;
		};

		inline dd_real Y() const
		{
			return y;
		};

		inline PointDd Mul(PointDd val) {
			return PointDd();
		};

		~PointDd();

	private:
		dd_real x;
		dd_real y;
	};

}

