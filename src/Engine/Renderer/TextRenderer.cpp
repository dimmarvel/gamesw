#include "TextRenderer.hpp"
#include "IO/Events/MapCreated.hpp"
#include <iostream>
#include <Engine/Map.hpp>

namespace sw::engine
{
	void TextRenderer::renderMap(const Map& map) 
	{
		uint32_t sizeY = map.getSizeY();
		uint32_t sizeX = map.getSizeX();

		for (uint32_t y = 0; y < sizeY; ++y) {
			for (uint32_t x = 0; x < sizeX; ++x) {
				Cell cell = map.getCellContent(x, y);
				auto cellUnit = cell.getUnit();
				if(cellUnit)
				{
					std::cout << cellUnit->getId();
				}
				else
					std::cout << ".";
			}
			std::cout << '\n';
		}
	}
}