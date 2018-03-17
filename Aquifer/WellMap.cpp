#include "WellMap.h"

void WellMap::initialize()
{
	std::string folder(R"(E:\projects\MastersDegree\Input\)");

	auto history = FileReader::readKeyword(folder + "HISTORY", "COMPDAT");

	for (const auto& element : *history)
	{
		auto toPieces = FileReader::breakLineToPieces(element);
		if (toPieces->empty())
		{
			continue;
		}
		const auto wellName = (*toPieces)[0];
		const auto xCoord = stod((*toPieces)[1], 0);
		const auto yCoord = stod((*toPieces)[2], 0);
		const auto lastZ = stod((*toPieces)[4], 0);

		auto existance = wellMap.find(wellName);
		if (existance != wellMap.end())
		{
			auto currentZ = existance->second.lastZ;
			if (currentZ > lastZ)
			{
				return;
			}//else update it
		}
		WellProperties wellProps(xCoord, yCoord, lastZ);
		wellMap[wellName] = wellProps;
	}
}

std::pair<int, int> WellMap::getCoordsByWellName(const std::string& wellName) const
{
	auto existance = wellMap.find(wellName);
	if (existance == wellMap.end())
	{
		return {-1, -1};
	}
	auto props = wellMap.at(wellName);
	return { props.x, props.y };
}