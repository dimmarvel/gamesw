#pragma once
#include "HealthComponent.hpp"
#include "IComponent.hpp"

namespace sw::engine
{
	class StrengthComponent final : public IComponent
	{
	private:
		int strength;

	public:
		explicit StrengthComponent(int streng) :
				strength(streng)
		{}

		inline int getStrength() const noexcept
		{
			return strength;
		}
	};
}
