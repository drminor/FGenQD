#pragma once

namespace qpvec
{
	class vHelper
	{
	public:

		inline double * createVec(int n)
		{
			double * result;
			result = new double[n];
			//for (int i = 0; i < n; i++)
			//{
			//	result[i] = 0.0;
			//}
			return result;
		}

		inline void clearVec(int n, double * vec)
		{
			for (int i = 0; i < n; i++)
			{
				vec[i] = 0.0;
			}
		}


		vHelper();
		~vHelper();
	};


}
