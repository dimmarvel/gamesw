#pragma once
#include "Swordsman.hpp"

#include "Components/StrengthComponent.hpp"
#include "Components/HealthComponent.hpp"
#include "Components/MovementComponent.hpp"
#include "Components/MeleeAttackComponent.hpp"
#include <IO/Events/UnitAttacked.hpp>
#include <IO/System/EventLog.hpp>

namespace sw::engine
{
	Swordsman::Swordsman(size_t id, Position pos, int hp, int strenght) 
	{
		setId(id);
		addComponent<HealthComponent>(hp);
		addComponent<StrengthComponent>(strenght);
		addComponent<MovementComponent>(pos);
		addComponent<MeleeAttackComponent>();
	}

	void Swordsman::attack(IUnit& target) {
		auto strenghtComp = getComponent<StrengthComponent>();
		if (strenghtComp)
		{
			auto targetHealth = target.getComponent<HealthComponent>();
			if (targetHealth) {
				targetHealth->takeDamage(strenghtComp->getStrength());
			}
		}
	}

	Position Swordsman::getPosition()
	{
		return getComponent<MovementComponent>()->getPosition();
	}
}