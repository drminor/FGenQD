#include "stdafx.h"
#include "Dd.h"
//#include <qd/dd_real.h>


using namespace System;

namespace qdDotNet {

	Dd::Dd(String^ val)
	{
		std::string strVal;
		MarshalString(val, strVal);
		qp temp = qp(strVal);
		this->hi = temp._hi();
		this->lo = temp._lo();
	}

}