

#pragma once
#include "IRenderer.hpp"

namespace sw::engine
{
	class Map;

	class TextRenderer : public IRenderer
	{
	public:
		void renderMap(const Map& map) override;
	};
}
