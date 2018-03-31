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
	auto source = m_sourceFolder;
	auto destiny = m_sourceFolder + "_Iteration_" + std::to_string(m_iterationNumber);
	m_currentIterationFolder = destiny;
	m_iterationNumber++;
	source = std::string("\"") + source + std::string("\"");
	destiny = std::string("\"") + destiny + std::string("\"");
	std::string command = std::string("xcopy") + std::string(" ") + source + std::string(" ") + destiny + std::string(" ") + std::string("/e") + std::string("/i") + std::string("/h");
	system(command.c_str());
}

void DataFileHandler::runIteration()
{
	copyFolder();

	auto dataPullPath = std::string("c:\\ecl\\2009.1\\bin\\pc\\eclipse.exe ") + removeDotData(m_name) + std::string("\n");
	auto batchFilePath = m_currentIterationFolder + std::string("\\") + std::string("runModel.bat");
	auto cdCommand = std::string("cd /d ") + m_currentIterationFolder + std::string("\n");
	ofstream batch;
	batch.open(batchFilePath, ios::out);
	batch << cdCommand;
	batch << "call c:\\ecl\\home\\$eclrc.bat\n";
	batch << "set ECLVER=2009.1\n";
	batch << "echo ----------------------------------------------------------------\n";
	batch << "echo STARTING SIMULATION\n";
	batch << "echo ----------------------------------------------------------------\n";
	batch << dataPullPath;
	batch << "echo ----------------------------------------------------------------\n";
	batch << "echo DONE\n";
	batch << "echo ----------------------------------------------------------------\n";
	batch.close();

	int i;
	printf("Checking if processor is available...");
	if (system(NULL)) puts("Ok");
	else exit(EXIT_FAILURE);
	printf("Executing command DIR...\n");
	i = system(batchFilePath.c_str());
	printf("The value returned was: %d.\n", i);

}

void DataFileHandler::splitFilename(const string& str)
{
	size_t found;
	found = str.find_last_of("/\\");
	m_sourceFolder = str.substr(0, found);
	m_name = str.substr(found + 1);
}

std::string DataFileHandler::removeDotData(const string& str)
{
	size_t found;
	found = str.find_last_of(".");
	return str.substr(0, found);
}
