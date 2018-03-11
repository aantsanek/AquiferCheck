#include "WaterLevelAnalyzer.h"
#include "FileReader.h"

void WaterLevelAnalyzer::fillWaterLevelTable()
{
	//read all files and get what needed
	std::string folder(R"(E:\projects\MastersDegree\Input\)");

	auto tops = FileReader::readFile(folder + "TOPS");
	auto sgas = FileReader::readFile(folder + "SGAS_2015");
	auto satnum = FileReader::readFile(folder + "SATNUM");


}
