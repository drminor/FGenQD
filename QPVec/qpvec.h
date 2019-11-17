#pragma once

#ifdef QPVEC_EXPORTS
#define QPVEC_API __declspec(dllexport)
#else
#define QPVEC_API __declspec(dllimport)
#endif

#include "stdafx.h"
#include "mkl.h"
#include "vHelper.h"
#include "twoSum.h"
#include "twoProd.h"



//extern "C" QPVEC_API void twosumA(double *a, double *b, double *s, double* err) {
//	qpvec::twoSum::two_sumA(a, b, s, err);
//}
