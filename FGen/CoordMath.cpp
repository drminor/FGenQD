#include "stdafx.h"
#include "CoordsMath.h"

namespace FGen
{
	CoordsMath::CoordsMath()
	{
	}

	CoordsDd CoordsMath::ZoomIn(CoordsDd coords, SizeInt samplePoints, RectangleInt area)
	{
		dd_real extentX = coords.EX() - coords.SX();
		dd_real hSt = coords.SX();
		int w = samplePoints.W();

		int ahStart = area.SX();
		dd_real nsx = CoordsMath::GetNewCoord(hSt, ahStart, extentX, w);

		int ahEnd = area.EX();
		dd_real nex = CoordsMath::GetNewCoord(hSt, ahEnd, extentX, w);

		dd_real extentY = coords.EY() - coords.SY();
		dd_real vSt = coords.SY();
		int h = samplePoints.H();

		int avStart = area.SY();
		dd_real nsy = CoordsMath::GetNewCoord(vSt, avStart, extentY, h);

		int avEnd = area.EY();
		dd_real ney = CoordsMath::GetNewCoord(vSt, avEnd, extentY, h);

		PointDd start = PointDd(nsx, nsy);
		PointDd end = PointDd(nex, ney);
		CoordsDd result = CoordsDd(start, end);
		return result;
	}

	dd_real CoordsMath::GetNewCoord(dd_real mSt, int pt, dd_real mExtent, int aExtent)
	{
		double aRat = pt / (double)aExtent;

		dd_real mOff = mExtent * aRat;
		dd_real nMPt = mSt + mOff;
		return nMPt;
	}

	CoordsDd CoordsMath::ZoomOut(CoordsDd coords, double amount)
	{
		dd_real deltaX = coords.Width() * amount / 2;
		dd_real deltaY = coords.Height() * amount / 2;

		PointDd start = PointDd(coords.SX() - deltaX, coords.SY() - deltaY);
		PointDd end = PointDd(coords.EX() + deltaX, coords.EY() + deltaY);

		CoordsDd result = CoordsDd(start, end);
		return result;
	}

	CoordsDd CoordsMath::ShiftRight(CoordsDd coords, double amount)
	{
		dd_real delta = coords.Width() * amount;

		PointDd start = PointDd(coords.SX() + delta, coords.SY());
		PointDd end = PointDd(coords.EX() + delta, coords.EY());

		CoordsDd result = CoordsDd(start, end);
		return result;
	}

	CoordsDd CoordsMath::ShiftUp(CoordsDd coords, double amount)
	{
		dd_real delta = coords.Height() * amount;

		PointDd start = PointDd(coords.SX(), coords.SY() + delta);
		PointDd end = PointDd(coords.EX(), coords.EY() + delta);

		CoordsDd result = CoordsDd(start, end);
		return result;
	}

	CoordsMath::~CoordsMath()
	{
	}
}
