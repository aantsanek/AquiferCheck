#pragma once
#include "common.h"

class DataFileHandler
{
	std::string m_sourceFolder;
	std::string m_currentIterationFolder;
	std::string m_name;
	std::vector<int> m_dimens;
	int m_iterationNumber = 1;

public:
	DataFileHandler() = default;
	~DataFileHandler() = default;
	void initialize(const std::string& filepath);
	void runIteration();

private:
	void splitFilename(const std::string& str);
	void copyFolder();
	std::string removeDotData(const std::string& str);
};

