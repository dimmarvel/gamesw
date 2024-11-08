#pragma once
#include <cstdint>
#include <fstream>

namespace sw::engine
{
	struct Settings final
	{
		int map_height{};
		int map_width{};
		std::ifstream& file;
	};
}