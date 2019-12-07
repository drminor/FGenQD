#include "stdafx.h"
#include "FGen.h"

#include <string>
#include <cctype>

#include "qpParser.h"

namespace FGen {

	//qp::qp()
	//{
	//}

	qp::qp(std::string const& s)
	{
		qpParser parser = qpParser();
		parser.Read(s, x[0], x[1]);

		//std::string result = parser.ToStr(x[0], x[1]);

	}

	qp::~qp()
	{
	}

	std::string qp::to_string()
	{
		qpParser parser = qpParser();

		std::string result = parser.ToStr(x[0], x[1]);
		return result;
	}

	//std::string qp::toHexString()
	//{
	//	return "1.0";
	//}

	//double qp::GetMantissa(double x, int &sign, int &exp)
	//{
	//	double significand;

	//	sign = (x >= 0) ? 1 : -1;    /*  deem 0 to be positive sign */
	//	significand = frexp(x, &exp);

	//	return significand;
	//}

}