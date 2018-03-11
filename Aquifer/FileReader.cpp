#include "FileReader.h"
using namespace std;

shared_ptr<vector<double>> FileReader::readFile()
{
	auto output = make_shared<vector<double>>();
	auto path = "E:\\NTG";
	ifstream file(path);
	
	if (!file.is_open())
	{
		//error
		return output;
	}

	string line;
	while (getline(file, line))
	{
		cout << line << '\n';

	}
	file.close();

	return output;
}
