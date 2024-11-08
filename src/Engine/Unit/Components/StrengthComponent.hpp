#pragma once
#include "IComponent.hpp"
#include "HealthComponent.hpp"

namespace sw::engine
{
	class StrengthComponent : public IComponent {
	private:
		int strength;

	public:
		
		explicit StrengthComponent(int streng) : strength(streng) {}
		inline int getStrength() const noexcept{ return strength; }
	};
}