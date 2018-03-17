#pragma once
#include "common.h"

class FileReader
{
public:
	FileReader() {}
	~FileReader() {}

	static std::shared_ptr<std::vector<std::string>> readAllFile(const std::string& path, const char delim = ' ');
	static std::shared_ptr<std::vector<std::string>> readKeyword(const std::string& path, const const std::string& keyword);
	static std::shared_ptr<std::vector<std::string>> breakLineToPieces(const const std::string& line, const char delim = ' ');

};

