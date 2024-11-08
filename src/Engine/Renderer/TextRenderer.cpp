#include "TextRenderer.hpp"

#include "IO/Events/MapCreated.hpp"

#include <Engine/Core/Map.hpp>
#include <iostream>

namespace sw::engine
{
	void TextRenderer::renderMap(const Map& map)
	{
		int sizeY = map.getSizeY();
		int sizeX = map.getSizeX();

		for (int y = 0; y < sizeY; ++y)
		{
			for (int x = 0; x < sizeX; ++x)
			{
				Cell cell = map.getCellContent(x, y);
				auto cellUnit = cell.getUnit();
				if (cellUnit)
				{
					std::cout << cellUnit->getId();
				}
				else
				{
					std::cout << "-";
				}
			}
			std::cout << '\n';
		}
	}
}
