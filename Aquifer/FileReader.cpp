#include "FileReader.h"
using namespace std;

shared_ptr<vector<string>> FileReader::readAllFile(const string& path)
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
		if (line == "/")
		{
			output->emplace_back(line);
			continue;
		}
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

std::shared_ptr<std::vector<std::string>> FileReader::readKeyword(const std::string & path, const std::string & keyword)
{
	auto output = make_shared<vector<string>>();
	ifstream file(path);

	if (!file.is_open())
	{
		//error
		return output;
	}

	string line;
	auto isKeywordSection = false;
	while (getline(file, line))
	{
		if (line == keyword)
		{
			isKeywordSection = true;
			continue;
		}
		if (!isKeywordSection)
		{
			continue;
		}
		if (line.substr(0, 2) == "--")//commented line
		{
			continue;
		}
		if (line == "/")
		{
			isKeywordSection = false;
			continue;
		}
		output->emplace_back(line);
	}
	file.close();

	return output;
}

std::shared_ptr<std::vector<std::string>> FileReader::breakLineToPieces(const const std::string & line)
{
	auto output = make_shared<vector<string>>();
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
	return output;
}


