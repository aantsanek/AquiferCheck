#include "FileReader.h"
using namespace std;

shared_ptr<vector<string>> FileReader::readFile(const string& path)
{
	auto output = make_shared<vector<string>>();
	ifstream file(path);
	
	if (!file.is_open())
	{
		//error
		return output;
	}

	string line;
	while (getline(file, line))
	{
		if (line.size() < 2)//questionable
		{
			continue;
		}
		if (line.substr(0,2) == "--")//commented line
		{
			continue;
		}
		std::stringstream ss(line);
		std::string item;
		while (getline(ss, item, ' '))
		{
			if (item == " " || item == "")
			{
				continue;
			}
			output->emplace_back(item);
		}
		
	}
	file.close();

	return output;
}
