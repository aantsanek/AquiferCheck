#include "FactReceiver.h"

void FactReceiver::getWaterLevel(const std::string& folder)
{
	//std::string folder(R"(E:\projects\MastersDegree\Input\)");

	auto factInput = FileReader::readAllFile(folder + "FACTWATERLEVEL.csv", ',');

	if (factInput->size() % 2 != 0)
	{
		//error
		return;
	}

	for (auto i = 0; i < factInput->size(); i+=2)
	{
		const auto wellName = (*factInput)[i];
		auto existance = factWaterLevel.find(wellName);
		if (existance != factWaterLevel.end())
		{
			//already exists
			return;
		}
		factWaterLevel[wellName] = stod((*factInput)[i+1], 0);
	}
}

double FactReceiver::getWaterLevelByWellName(const std::string& wellName) const
{
	auto existance = factWaterLevel.find(wellName);
	if (existance == factWaterLevel.end())
	{
		return -1;
	}
	return factWaterLevel.at(wellName);
}

std::vector<std::string> FactReceiver::getAllWellNames() const
{
	std::vector<std::string> output;

	for (auto wellName : factWaterLevel)
	{
		output.emplace_back(wellName.first);
	}
	return output;
}
