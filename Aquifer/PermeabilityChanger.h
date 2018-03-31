#pragma once
#include "common.h"
class PermeabilityChanger
{
	struct PermeabilityCube;
	std::shared_ptr<std::vector<PermeabilityCube>> m_data;
public:
	PermeabilityChanger()
	{
		m_data = std::make_shared<std::vector<PermeabilityCube>>();
	}
	~PermeabilityChanger() {}
	void fillData();
};

struct PermeabilityChanger::PermeabilityCube
{
	int x;
	int y;
	int z;
	double permz;
	PermeabilityCube() {}
	PermeabilityCube(const int x, const int y, const int z)
		: x{ x }, y{ y }, z{ z }
	{

	}
};
