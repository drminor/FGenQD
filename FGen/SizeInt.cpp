#include "stdafx.h"
#include "SizeInt.h"

namespace FGen
{
	SizeInt::SizeInt(int w, int h) : w(w), h(h)
	{
	}

	SizeInt::SizeInt()
	{
		w = 0;
		h = 0;
	}

	SizeInt::~SizeInt()
	{
	}
}
