#include "TextRenderer.hpp"
#include "IO/Events/MapCreated.hpp"
#include <iostream>
#include "Engine/Map.hpp"

namespace sw::engine
{
	void TextRenderer::renderMap(const Map& map) 
	{
		uint32_t width = map.getWidth();
		uint32_t height = map.getHeight();

		for (uint32_t y = 0; y < height; ++y) {
			for (uint32_t x = 0; x < width; ++x) {
				char content = map.getCellContent(x, y);
				std::cout << content << ' ';
			}
			std::cout << '\n';
		}
	}
}