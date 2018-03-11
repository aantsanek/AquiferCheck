#include "WaterLevelTable.h"

void WaterLevelTable::addBlock(const int x, const int y, const int z, const double depth)
{
	//table[{ x, y }].insert({ z, depth });

	auto xyPair = std::make_pair(x, y);
	auto zdepthPair = std::make_pair(z, depth);

	auto existance = table.find(xyPair);
	if (existance != table.end())
	{
		auto currentZ = existance->second.first;
		if (currentZ < z)
		{
			return;
		}//else update it
	}
	table[xyPair] = zdepthPair;
}

std::pair<int, double> WaterLevelTable::getDepth(const int x, const int y) const
{
	if (areValidCoords(x, y))
	{
		//warning
		return { -1, -1 };
	}

	auto depth = table.find({x, y});
	if (depth != table.end())
	{
		return depth->second;
	}
	return { -1, -1 };
}

bool WaterLevelTable::areValidCoords(const int x, const int y) const
{
	//TODO: is greater than maxX and maxY
	if (x < 0 || y < 0)
	{
		return false;
	}
	return true;
}
