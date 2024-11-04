#pragma once
#include <cstdint>

namespace sw::engine
{
	class Map;

	class IRenderer
	{
	public:
		virtual ~IRenderer() = default;
		virtual void renderMap(const Map& map) = 0;
	};
}