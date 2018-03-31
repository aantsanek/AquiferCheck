#include "DataFileHandler.h"
using namespace std;

void DataFileHandler::initialize(const std::string & filepath)
{
	ifstream file(filepath);
	
	if (!file.is_open())
	{
		//error
		return;
	}
	splitFilename(filepath);
	string line;
	auto dimensFound = false;
	while (getline(file, line))
	{
		if (dimensFound)
		{
			std::stringstream ss(line);
			std::string item;
			while (getline(ss, item, ' '))
			{
				if (m_dimens.size() == 3)
				{
					break;
				}
				m_dimens.emplace_back(stoi(item));
			}
			break;
		}
		if (line == "DIMENS")
		{
			dimensFound = true;
		}
	}
	file.close();

	return;
}

void DataFileHandler::copyFolder()
{
	auto source = m_folder;
	auto destiny = m_folder + "_Iteration_" + std::to_string(m_iterationNumber);
	m_iterationNumber++;
	source = std::string("\"") + source + std::string("\"");
	destiny = std::string("\"") + destiny + std::string("\"");
	std::string command = std::string("xcopy") + std::string(" ") + source + std::string(" ") + destiny + std::string(" ") + std::string("/e") + std::string("/i") + std::string("/h");
	system(command.c_str());
}

void DataFileHandler::splitFilename(const string& str)
{
	size_t found;
	found = str.find_last_of("/\\");
	m_folder = str.substr(0, found);
	m_name = str.substr(found + 1);
}
