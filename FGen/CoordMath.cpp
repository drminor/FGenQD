#include "stdafx.h"
#include "FGen.h"

namespace FGen
{
	CoordsMath::CoordsMath()
	{
	}

	CoordsDd CoordsMath::ZoomIn(CoordsDd coords, SizeInt samplePoints, RectangleInt area)
	{
		qp extentX = coords.EX() - coords.SX();
		qp hSt = coords.SX();
		int w = samplePoints.W();

		int ahStart = area.SX();
		qp nsx = CoordsMath::GetNewCoord(hSt, ahStart, extentX, w);

		int ahEnd = area.EX();
		qp nex = CoordsMath::GetNewCoord(hSt, ahEnd, extentX, w);

		qp extentY = coords.EY() - coords.SY();
		qp vSt = coords.SY();
		int h = samplePoints.H();

		int avStart = area.SY();
		qp nsy = CoordsMath::GetNewCoord(vSt, avStart, extentY, h);

		int avEnd = area.EY();
		qp ney = CoordsMath::GetNewCoord(vSt, avEnd, extentY, h);

		PointDd start = PointDd(nsx, nsy);
		PointDd end = PointDd(nex, ney);
		CoordsDd result = CoordsDd(start, end);
		return result;
	}

	qp CoordsMath::GetNewCoord(qp mSt, int pt, qp mExtent, int aExtent)
	{
		double aRat = pt / (double)aExtent;

		qp mOff = mExtent * aRat;
		qp nMPt = mSt + mOff;
		return nMPt;
	}

	CoordsDd CoordsMath::ZoomOut(CoordsDd coords, double amount)
	{
		qp deltaX = coords.Width() * amount / 2;
		qp deltaY = coords.Height() * amount / 2;

		PointDd start = PointDd(coords.SX() - deltaX, coords.SY() - deltaY);
		PointDd end = PointDd(coords.EX() + deltaX, coords.EY() + deltaY);

		CoordsDd result = CoordsDd(start, end);
		return result;
	}

	CoordsDd CoordsMath::ShiftRight(CoordsDd coords, double amount)
	{
		qp delta = coords.Width() * amount;

		PointDd start = PointDd(coords.SX() + delta, coords.SY());
		PointDd end = PointDd(coords.EX() + delta, coords.EY());

		CoordsDd result = CoordsDd(start, end);
		return result;
	}

	CoordsDd CoordsMath::ShiftUp(CoordsDd coords, double amount)
	{
		qp delta = coords.Height() * amount;

		PointDd start = PointDd(coords.SX(), coords.SY() + delta);
		PointDd end = PointDd(coords.EX(), coords.EY() + delta);

		CoordsDd result = CoordsDd(start, end);
		return result;
	}

	CoordsMath::~CoordsMath()
	{
	}
}
