
#pragma once
#include <memory>
#include <string>
#include <type_traits>
#include <stdexcept>
#include "Engine/Renderer/IRenderer.hpp"

namespace sw::engine
{
	class RendererFactory {
	public:
		template <typename RendererType, typename... Args>
		static std::unique_ptr<IRenderer> createRenderer(Args&&... args) {
			static_assert(std::is_base_of_v<IRenderer, RendererType>, 
				"RendererType must inherit from IRenderer");
			return std::make_unique<RendererType>(std::forward<Args>(args)...);
		}
	};
}
