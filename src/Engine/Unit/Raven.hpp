#pragma once
#include <iostream>
#include "IUnit.hpp"
#include "Components/AgilityComponent.hpp"
#include "Components/HPComponents.hpp"
#include <IO/Events/UnitAttacked.hpp>

class Raven : public IUnit {
public:
	Raven(size_t id, int hp, int agility)
	{
		set_id(id);
		addComponent<HPComponent>(hp);
		addComponent<AgilityComponent>(agility);
	}

	void move(int dx, int dy) {
		//TODO: do logs
	}

	void attack(IUnit& target) {
		auto agilityComp = getComponent<AgilityComponent>();
		if (agilityComp)
		{
			auto targetHealth = target.getComponent<HPComponent>();
			if (targetHealth) {
				targetHealth->takeDamage(agilityComp->agility);
				//TODO: do logs take damage mabue inside take damage
			}
		}
	}
};
