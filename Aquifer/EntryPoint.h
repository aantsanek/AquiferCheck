#pragma once
#include "common.h"
class EntryPoint
{
public:
	EntryPoint();
	~EntryPoint();

	static int doNothing(const std::string& input)
	{
		return input.size();
	}
};

