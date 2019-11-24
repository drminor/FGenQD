// QPVecTestConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include "../QPVec/qpvec.h"

#include "../QPVecClrWrapper/QPVecClrWrapper.h"

using namespace QPVecClrWrapper;

int main()
{
    std::cout << "Hello World!\n"; 

	qpvec::twoSum * t = new qpvec::twoSum(128);

	double * a = new double[128];
	double * b = new double[128];
	double * c = new double[128];
	double * d = new double[128];

	for (int i = 0; i < 128; i++) {
		a[i] = 1.2;
		b[i] = 3.4;

		c[i] = 0.0;
		c[i] = 0.0;
	}


	t->two_sumA(a, b, c, d);

	delete[] a, b, c, d;


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
