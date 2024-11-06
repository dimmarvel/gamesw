#pragma once
#include <cstdint>
#include <fstream>

namespace sw::engine
{
	struct Settings
	{
		uint32_t map_height{};
		uint32_t map_width{};
		std::ifstream& file;
	};
}