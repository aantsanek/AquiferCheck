#include "EntryPoint.h"
#include <iostream>
EntryPoint::EntryPoint()
{
}


EntryPoint::~EntryPoint()
{
}

extern "C" __declspec(dllexport) int doNothing(const char* input)
{
	std::string x(input);
	//return 11;
	std::cout << x;
	return EntryPoint::doNothing(x);
}

extern "C" __declspec(dllexport) void calculateButtonClicked()
{
	//run the algorithm here
}