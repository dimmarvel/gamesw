#pragma once
#include "IComponent.hpp"
#include "HPComponent.hpp"

namespace sw::engine
{
	class AgilityComponent : public IComponent {
	public:
		int agility;
		
		AgilityComponent(int agil) : agility(agil) {}
	};
}