#include "PermeabilityChanger.h"
using namespace std;

void PermeabilityChanger::fillData()
{
	std::string folder(R"(E:\projects\MastersDegree\Input\)");

	auto permzData = FileReader::readAllFile(folder + "PERMZ");

	//razm = DX * DY * DZ
	//razm = 90 * 20 * 61
	auto dx = 90;
	auto dy = 20;
	auto dz = 61;
	auto fullSize = dx * dy * dz;
	m_data->resize(fullSize);
	auto x = 1;
	auto y = 1;
	auto z = 1;
	for (auto i = 0; i < m_data->size(); i++)
	{
		(*m_data)[i] = { x, y, z };
		if (x == dx) y++;
		if (x == dx) x = 0;
		if (y == dy + 1) z++;
		if (y == dy + 1) y = 1;
		x++;
	}
	auto i = 0;
	bool toAdd = false;
	for (const auto& item : *permzData)
	{
		if (item == "/")
		{
			toAdd = false;
		}
		if (toAdd)
		{
			(*m_data)[i].permz = stod(item, 0);
			i++;
		}
		if (item == "PERMZ")
		{
			toAdd = true;
		}
	}
}