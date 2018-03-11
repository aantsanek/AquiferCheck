#pragma once
#include "common.h"

class FileReader
{
public:
	FileReader() {}
	~FileReader() {}

	static std::shared_ptr<std::vector<std::string>> readFile(const std::string& path);
};

