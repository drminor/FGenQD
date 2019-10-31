#pragma once

#include "SizeInt.h"
#include "PointInt.h"
namespace FGen
{
	struct RectangleInt
	{

	public:
		RectangleInt();
		RectangleInt(PointInt point, SizeInt size);
		RectangleInt(int x, int y, int w, int h);

		inline PointInt Point() const
		{
			return point;
		};

		inline SizeInt Size() const
		{
			return size;
		};

		inline int SX() const
		{
			return point.X();
		};

		inline int SY() const
		{
			return point.Y();
		};

		inline int EX() const
		{
			return point.X() + size.W();
		};

		inline int EY() const
		{
			return point.Y() + size.H();
		};

		inline int W() const
		{
			return size.W();
		};

		inline int H() const
		{
			return size.H();
		};

		~RectangleInt();

	private:
		SizeInt size;
		PointInt point;
	};

}


