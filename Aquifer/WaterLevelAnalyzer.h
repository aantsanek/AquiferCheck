#pragma once
#include "common.h"
#include "WaterLevelTable.h"

class WaterLevelAnalyzer
{
	std::shared_ptr<WaterLevelTable> m_table;
	struct CubeData;
public:
	WaterLevelAnalyzer() 
	{
		m_table = std::make_shared<WaterLevelTable>();
	}
	~WaterLevelAnalyzer() {}

	void fillWaterLevelTable();
	double getDifferenceLevelModelFact(const int x, const int y, const double factLevel);
private:
	void WaterLevelAnalyzer::fillData(const std::shared_ptr<std::vector<CubeData>>& data,
									  const std::shared_ptr<std::vector<std::string>>& readArray,
									  const std::string& name);
};

struct WaterLevelAnalyzer::CubeData
{
	int x;
	int y;
	int z;
	double top;
	double sgas;
	int satnum;

	CubeData() {}

	CubeData(const int x, const int y, const int z)
		: x{ x }, y{ y }, z{ z }
	{

	}
	bool isCubeWater() const;
};