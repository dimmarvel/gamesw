#include "Hunter.hpp"

#include "Components/AgilityComponent.hpp"
#include "Components/HealthComponent.hpp"
#include "Components/MeleeAttackComponent.hpp"
#include "Components/RangeAttackComponent.hpp"
#include "Components/RangeComponent.hpp"
#include "Components/StrengthComponent.hpp"

namespace sw::engine
{
	Hunter::Hunter(size_t id, Position pos, int health, int agility, int strenght, int range)
	{
		setId(id);
		setType(UnitType::Hunter);
		addComponent<HealthComponent>(health);
		addComponent<StrengthComponent>(strenght);
		addComponent<AgilityComponent>(agility);
		addComponent<RangeAttackComponent>(2, range);
		addComponent<MovementComponent>(pos);
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
		auto rangeComp = getComponent<RangeAttackComponent>();
		if (!rangeComp)
		{
			throw std::runtime_error("For Hunter, RangeAttackComponent doesnt exist");
		}
		auto targetHealth = target.getComponent<HealthComponent>();

		if (targetHealth)
		{
			targetHealth->takeDamage(meleeDamage());
		}
	}

	void Hunter::meleeAttack(IUnit& target)
	{
		auto rangeComp = getComponent<RangeAttackComponent>();
		if (!rangeComp)
		{
			throw std::runtime_error("For Hunter, RangeAttackComponent doesnt exist");
		}

		auto targetHealth = target.getComponent<HealthComponent>();
		if (targetHealth)
		{
			targetHealth->takeDamage(getComponent<AgilityComponent>()->getAgility());
		}
	}
}
