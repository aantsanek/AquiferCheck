#include "WaterLevelAnalyzer.h"
#include "FileReader.h"
using namespace std;

void WaterLevelAnalyzer::fillWaterLevelTable()
{
	//read all files and get what needed
	std::string folder(R"(E:\projects\MastersDegree\Input\)");

	auto tops = FileReader::readFile(folder + "TOPS");
	auto sgas = FileReader::readFile(folder + "SGAS_2015");
	auto satnum = FileReader::readFile(folder + "SATNUM");
	auto phases = FileReader::readFile(folder + "PHASES");

	//razm = DX * DY * DZ
	//razm = 90 * 20 * 61
	auto dx = 90;
	auto dy = 20;
	auto dz = 61;
	auto fullSize = dx * dy * dz;

	auto data = make_shared<vector<CubeData>>(fullSize); //x,y,z,top, sgas, satnum

	auto x = 1;
	auto y = 1;
	auto z = 1;
	for (auto i = 0; i < data->size(); i++)
	{
		(*data)[i] = { x, y, z };
		if (x == dx) y++;
		if (x == dx) x = 0;
		if (y == dy + 1) z++;
		if (y == dy + 1) y = 1;
		x++;
	}

	fillData(data, tops, "TOPS");
	fillData(data, sgas, "SGAS");
	fillData(data, satnum, "SATNUM");

	for (const auto& cube : *data)
	{
		if (cube.isCubeWater())
		{
			m_table->addBlock(cube.x, cube.y, cube.z, cube.top);
		}
	}

}

void WaterLevelAnalyzer::fillData(const shared_ptr<vector<CubeData>>& data, const shared_ptr<vector<string>>& readArray, const string& name)
{
	auto i = 0;
	bool toAdd = false;
	for (const auto& item : *readArray)
	{
		if (item == "/")
		{
			toAdd = false;
		}
		if (toAdd)
		{
			if (name == "TOPS")
			{
				(*data)[i].top = stod(item, 0);
			}
			if (name == "SGAS")
			{
				(*data)[i].sgas = stod(item, 0);
			}
			if (name == "SATNUM")
			{
				(*data)[i].satnum = static_cast<int>(stod(item, 0));
			}
			i++;
		}
		if (item == name)
		{
			toAdd = true;
		}
	}
}

bool WaterLevelAnalyzer::CubeData::isCubeWater() const
{
	if (sgas > 0.3)
	{
		return false;
	}
	return true;
}
