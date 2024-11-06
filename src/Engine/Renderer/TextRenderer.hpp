#pragma once
#include "IRenderer.hpp"

namespace sw::engine
{
	class Map;

	class TextRenderer : public IRenderer
	{
	public:
		TextRenderer() = default;
		virtual ~TextRenderer() = default;

		void renderMap(const Map& map) override;
	};
}
