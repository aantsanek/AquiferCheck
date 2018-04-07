#include "EntryPoint.h"
#include "WaterLevelAnalyzer.h"
#include "WellMap.h"
#include "FactReceiver.h"
#include "DataFileHandler.h"
#include "PermeabilityChanger.h"

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
/*
We have three maps
First map from waterLevelAnalyzer
	shows model water level for a given SGAS
	[x,y] -> [z, depth]
Second map from WellMap
	shows coords of a given well
	[wellname] -> [x,y,deepestZ]
Third map from FactReceiver
	shows fact water level read from csv
	[wellname] -> [depth]
*/

extern "C" __declspec(dllexport) void calculateButtonClicked()
{
	PermeabilityChanger pc;
	pc.fillData();
	pc.changePerm(15, 9, 18);


	DataFileHandler dfh;
	std::string folder(R"(E:\projects\MastersDegree\Input\PROJECT.DATA)");
	dfh.initialize(folder);
	dfh.runIteration();


	//run the algorithm here
	WaterLevelAnalyzer analyzer;
	analyzer.fillWaterLevelTable();
	WellMap wellMap;
	wellMap.initialize();
	FactReceiver fact;
	fact.getWaterLevel();
	std::map<std::string, double> results;
	for (auto wellName : fact.getAllWellNames())
	{
		auto xy = wellMap.getCoordsByWellName(wellName);
		auto factLevel = fact.getWaterLevelByWellName(wellName);
		auto result = analyzer.getDifferenceLevelModelFact(xy.first, xy.second, factLevel);
		results[wellName] = result;
	}

	//results table should be printed to file somewhere (#0 iteration)
	//and now we need to read perfZ to change some values there

	//after run eclipse and get results

	//repeat
}