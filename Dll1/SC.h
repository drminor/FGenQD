#pragma once

#ifdef DLL1_EXPORTS
#define DLL1_API __declspec(dllexport)
#else
#define DLL1_API __declspec(dllimport)
#endif

class DLL1_API SC
{
public:
	SC();
	~SC();


	int Test1(int a, int b);

	double VAdd();

};

