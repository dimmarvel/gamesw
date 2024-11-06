#pragma once
#include "IComponent.hpp"
#include "HPComponents.hpp"

namespace sw::engine
{
	class StrengthComponent : public IComponent {
	public:
		int strength;
		
		explicit StrengthComponent(int streng) : strength(streng) {}
	};
}