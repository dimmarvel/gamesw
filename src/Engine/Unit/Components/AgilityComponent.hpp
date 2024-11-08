#pragma once
#include "IComponent.hpp"
#include "HealthComponent.hpp"

namespace sw::engine
{
	class AgilityComponent : public IComponent
	{
	private:
		int agility;

	public:

		AgilityComponent(int agil) : agility(agil) {}
		inline int getAgility() const noexcept { return agility; }
	};
}