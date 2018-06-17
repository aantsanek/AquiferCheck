#pragma once
#include "common.h"

class WaterLevelTable
{
	std::map<std::pair<int, int>, std::pair<int, double>> table;
	
public:
	WaterLevelTable() {}
	~WaterLevelTable() {}

	void addBlock(const int x, const int y, const int z, const double depth);
	std::pair<int, double> getDepth(const int x, const int y) const;

private:
	bool areValidCoords(const int x, const int y) const;
};
