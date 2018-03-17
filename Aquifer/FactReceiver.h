#pragma once
#include "common.h"

class FactReceiver
{
	std::map<std::string, double> factWaterLevel;
public:
	FactReceiver() = default;
	~FactReceiver() = default;
	void getWaterLevel();
	double getWaterLevelByWellName(const std::string& wellName) const;
	std::vector<std::string> getAllWellNames() const;
};

