#include "WaterLevelTable.h"

void WaterLevelTable::addBlock(const int x, const int y, const int z, const double depth)
{
	table.push_back({ x, y, z, depth });
}

std::pair<int, double> WaterLevelTable::getDepth(const int x, const int y) const
{
	if (areValidCoords(x, y))
	{
		//warning
		return { -1, -1 };
	}
	//TODO: faster algorithm
	for (const auto& block : table)
	{
		if (block.x == x && block.y == y)
		{
			return { block.z, block.depth };
		}
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
