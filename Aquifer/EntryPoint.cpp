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

extern "C" __declspec(dllexport)
void calculateButtonClicked(const char* dataPath, const char* folderPath)
{
	DataFileHandler dfh;
	//std::string folder(R"(E:\projects\MastersDegree\Input\)");
	std::string folder(folderPath);
	folder += "\\";
	std::string dataPathString(dataPath);
	dfh.initialize(dataPathString);

	WellMap wellMap;
	wellMap.initialize(folder);
	FactReceiver fact;
	fact.getWaterLevel(folder);

	const auto maxNumberOfIterations = 2;
	std::map<std::string, double> results;
	for (auto iteration = 0; iteration < maxNumberOfIterations; iteration++)
	{
		WaterLevelAnalyzer analyzer;
		analyzer.fillWaterLevelTable(folder);

		if (iteration != 0)
		{
			PermeabilityChanger pc;
			pc.fillData(folder);
			for (auto pair : results)
			{
				if (std::abs(pair.second) > 3)
				{
					auto coordsXY = wellMap.getCoordsByWellName(pair.first);
					auto lastZ = wellMap.getZByWellName(pair.first);
					pc.changePerm(coordsXY.first, coordsXY.second, lastZ);
				}
			}
			pc.saveChanges();
		}

		
		std::vector<std::string> resultsToCSV;
		resultsToCSV.emplace_back("Well Name, Fact Level, Model Level, Difference");
		for (auto wellName : fact.getAllWellNames())
		{
			auto xy = wellMap.getCoordsByWellName(wellName);
			auto factLevel = fact.getWaterLevelByWellName(wellName);
			auto result = analyzer.getDifferenceLevelModelFact(xy.first, xy.second, factLevel);
			auto modelLevel = factLevel - result;
			results[wellName] = result;
			resultsToCSV.emplace_back(wellName + "," + std::to_string(factLevel) + "," + std::to_string(modelLevel) + "," + std::to_string(result));
		}
		FileWriter::writeResultsCSV(folder + "RESULTS.csv", resultsToCSV);

		if (iteration != maxNumberOfIterations - 1)
		{
			folder = dfh.runIteration();
			folder += "\\";
		}
	}
	
	


	//run the algorithm here
	
	//results table should be printed to file somewhere (#0 iteration)
	//and now we need to read perfZ to change some values there

	//after run eclipse and get results

	//repeat
}