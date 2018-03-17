#include "EntryPoint.h"
#include "WaterLevelAnalyzer.h"
#include "WellMap.h"

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
///////WaterLevelAnalyzer analyzer;
///////analyzer.fillWaterLevelTable();
	//OK WE HAVE A TABLE WITH WATER LEVEL

	//Now we need to compare it with fact
	WellMap wellMap;
	wellMap.initialize();
}