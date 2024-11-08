#pragma once
#include "Hunter.hpp"

#include "Components/StrengthComponent.hpp"
#include "Components/AgilityComponent.hpp"
#include "Components/RangeComponent.hpp"
#include "Components/HealthComponent.hpp"
#include "Components/MeleeAttackComponent.hpp"
#include "Components/RangeAttackComponent.hpp"

namespace sw::engine
{
	Hunter::Hunter(size_t id, Position pos, int health, int agility, int strenght, int range)
	{
		setId(id);
		addComponent<HealthComponent>(health);
		addComponent<StrengthComponent>(strenght);
		addComponent<AgilityComponent>(agility);
		addComponent<RangeComponent>(agility);
		addComponent<MovementComponent>(pos);
		addComponent<RangeAttackComponent>();
		addComponent<MeleeAttackComponent>();
	}

	uint32_t Hunter::meleeDamage()
	{
		return getComponent<StrengthComponent>()->getStrength();
	}

	Position Hunter::getPosition()
	{
		return getComponent<MovementComponent>()->getPosition();
	}

	void Hunter::rangeAttack(IUnit& target)
	{
		auto rangeComp = getComponent<RangeComponent>();
		if (!rangeComp)
			throw std::runtime_error("For Hunter, RangeComponent doesnt exist");
		auto targetHealth = target.getComponent<HealthComponent>();

		if (targetHealth)
			targetHealth->takeDamage(meleeDamage());
	}

	void Hunter::meleeAttack(IUnit& target)
	{
		auto rangeComp = getComponent<RangeComponent>();
		if (!rangeComp)
			throw std::runtime_error("For Hunter, RangeComponent doesnt exist");

		auto targetHealth = target.getComponent<HealthComponent>();
		if (targetHealth) 
			targetHealth->takeDamage(getComponent<AgilityComponent>()->getAgility());
	}
}