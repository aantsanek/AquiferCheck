#pragma once
#include "common.h"
class WellMap
{
	struct WellProperties;
	std::map<std::string, WellProperties> wellMap;
public:
	WellMap() = default;
	~WellMap() = default;

	void initialize();
	std::pair<int, int> getCoordsByWellName(const std::string& wellName) const;
};

struct WellMap::WellProperties
{
	int x;
	int y;
	int lastZ;
	WellProperties() = default;
	WellProperties(const int _x, const int _y, const int _lastZ)
		: x{_x}, y{_y}, lastZ{_lastZ}
	{
	}
};

