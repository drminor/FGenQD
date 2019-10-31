#pragma once

#include <qd/dd_real.h>

using namespace System;

namespace qdDotNet {

	public value struct Dd
	{
		double hi;
		double lo;

		Dd(double hi, double lo)
		{
			this->hi = hi;
			this->lo = lo;
		}

		Dd(double hi)
		{
			this->hi = hi;
			this->lo = 0;
		}

		Dd(dd_real val)
		{
			this->hi = val._hi();
			this->lo = val._lo();
		}

		Dd(String^ val);

		dd_real ToDdReal()
		{
			dd_real result = dd_real(this->hi, this->lo);
			return result;
		}

		String^ GetStringVal()
		{
			dd_real temp = ToDdReal();
			std::string strVal = temp.to_string();

			String^ result = gcnew String(strVal.c_str());

			return result;
		}

	};

	inline void MarshalString(String ^ s, std::string& os) {
		using namespace Runtime::InteropServices;
		const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}

}
