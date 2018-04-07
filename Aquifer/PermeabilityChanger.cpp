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
	m_dimX = dx;
	m_dimY = dy;
	m_dimZ = dz;
	auto fullSize = dx * dy * dz;
	auto tempXYZStorage = std::make_shared<std::vector<PermeabilityCube>>();
	tempXYZStorage->resize(fullSize);
	auto x = 1;
	auto y = 1;
	auto z = 1;
	for (auto i = 0; i < tempXYZStorage->size(); i++)
	{
		(*tempXYZStorage)[i] = { x, y, z };
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
			//(*m_data)[i].permz = stod(item, 0);
			xyz currentXYZ{ (*tempXYZStorage)[i].x, (*tempXYZStorage)[i].y, (*tempXYZStorage)[i].z };
			const auto value = stod(item, 0);
			(*m_data)[currentXYZ] = value;
			i++;
		}
		if (item == "PERMZ")
		{
			toAdd = true;
		}
	}
	tempXYZStorage->clear();
}

void PermeabilityChanger::changePerm(const int x, const int y, const int lowestZ)
{//APPLY MATH HERE!
	const int range = 10;//TODO:use in arguments
	const auto xRange = getRangeX(x, range);
	const auto yRange = getRangeY(y, range);
	const auto zRange = getRangeZ(lowestZ, 20);
	const auto average = findAveragePerm(xRange, yRange, zRange);
	const auto stdDeviation = findStdDeviation(xRange, yRange, zRange, average);
	
	const double epsilon = 100;//if difference more than epsilon in percents %

	const double lower = average - stdDeviation;
	const double higher = average + stdDeviation;
	for (auto x = xRange.first; x < xRange.second; x++)
	{
		for (auto y = yRange.first; y < yRange.second; y++)
		{
			for (auto z = zRange.first; z < zRange.second; z++)
			{
				auto value = (*m_data)[{x, y, z}];
				if (value == 0)
				{
					continue;
				}
				if (value < lower || value > higher)
				{
					(*m_data)[{x, y, z}] = average;
				}
			}
		}
	}
	const auto average2 = findAveragePerm(xRange, yRange, zRange);
	const auto stdDeviation2 = findStdDeviation(xRange, yRange, zRange, average);
}

double PermeabilityChanger::findAveragePerm(const std::pair<int, int>& xRange, const std::pair<int, int>& yRange, const std::pair<int, int>& zRange)
{
	//TODO: find smart mathematical solution
	double sum = 0;
	int size = 0;
	for (auto x = xRange.first; x < xRange.second; x++)
	{
		for (auto y = yRange.first; y < yRange.second; y++)
		{
			for (auto z = zRange.first; z < zRange.second; z++)
			{
				auto value = (*m_data)[{x, y, z}];
				if (value == 0)
				{
					continue;
				}
				sum += value;
				size++;
			}
		}
	}
	return sum / size;
}

double PermeabilityChanger::findStdDeviation(const std::pair<int, int>& xRange, const std::pair<int, int>& yRange, const std::pair<int, int>& zRange, const double average)
{
	double squaredSum = 0;
	int size = 0;
	for (auto x = xRange.first; x < xRange.second; x++)
	{
		for (auto y = yRange.first; y < yRange.second; y++)
		{
			for (auto z = zRange.first; z < zRange.second; z++)
			{
				auto value = (*m_data)[{x, y, z}];
				if (value == 0)
				{
					continue;
				}
				squaredSum += ((value - average)*(value - average));
				size++;
			}
		}
	}
	return std::sqrt(squaredSum / (size-1));
}

std::pair<double, double> PermeabilityChanger::getRangePerm(const double average, const double epsilon)
{

	return {};
}

std::pair<int, int> PermeabilityChanger::getRangeX(const int index, const int range)
{
	auto lower = index - range;
	auto higher = index + range;
	return { std::max(lower, 0), std::min(higher, m_dimX) };
}

std::pair<int, int> PermeabilityChanger::getRangeY(const int index, const int range)
{
	auto lower = index - range;
	auto higher = index + range;
	return { std::max(lower, 0), std::min(higher, m_dimY) };
}

std::pair<int, int> PermeabilityChanger::getRangeZ(const int index, const int range)
{
	if (range == 0)
	{
		return { std::max(index, 0), m_dimZ };
	}
	return { std::max(index, 0), std::min(index + range, m_dimZ) };
}