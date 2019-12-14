#pragma once

#ifdef FGEN_EXPORTS
#define FGEN_API __declspec(dllexport)
#else
#define FGEN_API __declspec(dllimport)
#endif

#include <string>

namespace FGen
{
	class FGEN_API qp
	{

	public:

		double _hi() const { return x[0]; }
		double _lo() const { return x[1]; }

		void resetToZero() {
			x[0] = 0;
			x[1] = 0;
		}

		double toDouble() const
		{
			return _hi() + _lo();
		}

		std::string to_string();

		qp()
		{
			x[0] = 0.0;
			x[1] = 0.0;
		}

		qp(double h)
		{
			x[0] = h;
			x[1] = 0.0;
		}

		qp(double hi, double lo)
		{
			x[0] = hi;
			x[1] = lo;
		}

		qp(std::string const& s);

		~qp();

	private:
		double x[2];

	};

}

