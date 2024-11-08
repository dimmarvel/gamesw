#pragma once

namespace sw::engine
{
	class Map;

	/**
	 * @class IRenderer
	 * @brief An abstract base class for rendering map data.
	 * This class defines an interface for rendering a map. Any class that implements this interface
	 * must provide the `renderMap` method to render the map to a specific output (e.g., console, GUI, etc.).
	 * It is meant to be extended by concrete renderer classes like `TextRenderer` or `GraphicalRenderer`.
	 */
	class IRenderer
	{
	public:
		virtual ~IRenderer() = default;
		/**
		 * @brief Renders the map to a specific output.
		 * This pure virtual function requires an implementation in derived classes to render the map.
		 * The `map` parameter contains the state of the map that needs to be displayed.
		 * @param map The map to render.
		 */
		virtual void renderMap(const Map& map) = 0;
	};
}
