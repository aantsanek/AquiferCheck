#pragma once
#include "common.h"
#include "WaterLevelTable.h"

class WaterLevelAnalyzer
{
	std::shared_ptr<WaterLevelTable> m_table;

public:
	WaterLevelAnalyzer() 
	{
		m_table = std::make_shared<WaterLevelTable>();
	}
	~WaterLevelAnalyzer() {}

	void fillWaterLevelTable();
};

