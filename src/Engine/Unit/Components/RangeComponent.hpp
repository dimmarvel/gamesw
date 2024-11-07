#pragma once
#include "IComponent.hpp"
#include "HPComponent.hpp"

namespace sw::engine
{
	class RangeComponent : public IComponent {
	public:
		int range;
		
		explicit RangeComponent(int r) : range(r) {}
	};
}