#pragma once
#include "common.h"

class FileWriter
{
public:
	FileWriter() {}
	~FileWriter() {}

	static void changeKeyword(const std::string& path, const std::string& keyword, const std::vector<std::string>& lines);
};

