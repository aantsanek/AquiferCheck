#pragma once
#include "common.h"

struct xyz
{
	int x;
	int y;
	int z;
	xyz(const int x, const int y, const int z)
		: x{ x }, y{ y }, z{ z }
	{

	}

	bool operator< (const xyz& n) const
	{
		if (z == n.z)
		{
			if (y == n.y)
			{
				return x < n.x;
			}
			return y < n.y;
		}
		return z < n.z;
	}
};

class PermeabilityChanger
{
	struct PermeabilityCube;
	std::shared_ptr<std::map<xyz, double>> m_data;
	int m_dimX;
	int m_dimY;
	int m_dimZ;
	std::string m_folder;
public:
	PermeabilityChanger()
	{
		m_data = std::make_shared<std::map<xyz, double>>();
	}
	~PermeabilityChanger() {}
	void fillData(const std::string& folder);
	void changePerm(const int x, const int y, const int lowestZ);
	double findAveragePerm(const std::pair<int, int>& xRange, const std::pair<int, int>& yRange, const std::pair<int, int>& zRange);
	double findStdDeviation(const std::pair<int, int>& xRange, const std::pair<int, int>& yRange, const std::pair<int, int>& zRange, const double average);
	std::pair<int, int> getRangeX(const int index, const int range);
	std::pair<int, int> getRangeY(const int index, const int range);
	std::pair<int, int> getRangeZ(const int index, const int range = 0);
	std::pair<double, double> getRangePerm(const double average, const double epsilon);
	void saveChanges();
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
