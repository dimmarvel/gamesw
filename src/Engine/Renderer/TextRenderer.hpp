#pragma once
#include "IRenderer.hpp"

namespace sw::engine
{
	class Map;

	/**
	 * @class TextRenderer
	 * @brief A renderer that outputs the map to the console in text format.
	 * 
	 * This class implements the IRenderer interface and provides functionality to render a map
	 * by displaying units or empty cells as text on the console.
	 */
	class TextRenderer : public IRenderer
	{
	public:
		TextRenderer() = default;
		virtual ~TextRenderer() = default;

		/**
		 * @brief Renders the map to the console.
		 * 
		 * This method outputs the current state of the map to the console. Each cell in the map
		 * is displayed as either a unit ID (if the cell contains a unit) or a dash ('-') to indicate
		 * an empty cell. The map is rendered row by row, with each unit ID or empty cell printed
		 * in a grid-like format.
		 *
		 * @param map The map to render.
		 */
		void renderMap(const Map& map) override;
	};
}
