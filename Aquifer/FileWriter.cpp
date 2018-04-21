#include "FileWriter.h"
using namespace std;

void FileWriter::changeKeyword(const std::string& path, const std::string & keyword, const std::vector<std::string>& lines)
{
	auto beforeKeyword = make_shared<vector<string>>();
	auto afterKeyword = make_shared<vector<string>>();
	ifstream ifile(path);

	if (!ifile.is_open())
	{
		//error
		return;
	}

	string line;
	auto isKeywordSection = false;
	auto isAfterKeyword = false;
	while (getline(ifile, line))
	{
		if (line == keyword)
		{
			isKeywordSection = true;
			isAfterKeyword = true;
			continue;
		}
		if (isKeywordSection)
		{
			continue;
		}
		if (isAfterKeyword)
		{
			afterKeyword->emplace_back(line);
		}
		else
		{
			beforeKeyword->emplace_back(line);
		}
		if (line == "/")
		{
			isKeywordSection = false;
		}
	}
	ifile.close();

	ofstream ofile;
	ofile.open(path);
	for (const auto string : *beforeKeyword)
	{
		ofile << string << '\n';
	}
	for (const auto string : lines)
	{
		ofile << string << '\n';
	}
	for (const auto string : *afterKeyword)
	{
		ofile << string << '\n';
	}
	ofile.close();
}
