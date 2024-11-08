#pragma once
#include "HealthComponent.hpp"
#include "IComponent.hpp"

namespace sw::engine
{
	class AgilityComponent final : public IComponent
	{
	private:
		int agility;

	public:
		AgilityComponent(int agil) :
				agility(agil)
		{}

		inline int getAgility() const noexcept
		{
			return agility;
		}
	};
}
