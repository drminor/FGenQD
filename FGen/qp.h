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
			//x[0] = qd::two_sum(hi, lo, x[1]);
			//TODO: Fix Me
			x[0] = hi;
			x[1] = lo;
		}

		qp(std::string const& s);
		//std::string toHexString();

		~qp();

		int read(std::string const & s, qp & a);


	private:
		double x[2];

		//double GetMantissa(double x, int &sign, int &exp);

	};


	inline bool operator>(qp const& a, double b)
	{
		return a._hi() > b;
	}

	inline qp operator+(qp const& a, qp const& b)
	{
		return qp(a._hi() + b._hi());
	}

	inline qp operator+(qp const& a, double b)
	{
		return qp(a._hi() + b);
	}

	inline qp operator+(double a, qp const& b)
	{
		return qp(a + b._hi());
	}

	inline qp operator-(qp const& a, qp const& b)
	{
		return qp(a._hi() - b._hi());
	}

	inline qp operator-(qp const& a, double b)
	{
		return qp(a._hi() - b);
	}

	inline qp operator-(double a, qp const& b)
	{
		return qp(a - b._hi());
	}

	inline qp operator*(qp const& a, qp const& b)
	{
		return qp(a._hi() * b._hi());
	}

	inline qp operator*(qp const& a, double b)
	{
		return qp(a._hi() * b);
	}

	inline qp operator*(double a, qp const& b)
	{
		return qp(a * b._hi());
	}

	inline qp operator/(qp const& a, qp const& b)
	{
		return qp(a._hi() / b._hi());
	}

	inline qp operator/(qp const& a, double b)
	{
		return qp(a._hi() / b);
	}

	inline qp operator/(double a, qp const& b)
	{
		return qp(a / b._hi());
	}
}

