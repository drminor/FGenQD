#pragma once

namespace FGen
{
	struct PointInt
	{

	public:
		PointInt();
		PointInt(int x, int y);

		inline int X() const
		{
			return x;
		};

		inline int Y() const
		{
			return y;
		};

		~PointInt();

	private:
		int x;
		int y;
	}; 

}

