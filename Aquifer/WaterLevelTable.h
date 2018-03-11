#pragma once
#include "common.h"

class WaterLevelTable
{
	struct WaterLevelBlock;
	std::vector<WaterLevelBlock> table;
	
public:
	WaterLevelTable() {}
	~WaterLevelTable() {}

	void addBlock(const int x, const int y, const int z, const double depth);
	std::pair<int, double> getDepth(const int x, const int y) const;

private:
	bool areValidCoords(const int x, const int y) const;
};

struct WaterLevelTable::WaterLevelBlock
{
	//For each x and y -> get water level (its Zcoord and depth of that coord)
	int x;
	int y;
	int z;
	double depth;

	WaterLevelBlock(const int x, const int y, const int z, const double depth)
		: x{ x }, y{ y }, z{ z }, depth{ depth }
	{
	}

	~WaterLevelBlock() {}
};

