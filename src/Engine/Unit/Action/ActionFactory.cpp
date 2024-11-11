#include "ActionFactory.hpp"

#include "MeleeAttackAction.hpp"
#include "MoveAction.hpp"
#include "RangeAttackAction.hpp"
#include "HealAction.hpp"

#include <Engine/Core/Map.hpp>
#include <Engine/Core/Position.hpp>
#include <Engine/Unit/Components/AgilityComponent.hpp>
#include <Engine/Unit/Components/MeleeAttackComponent.hpp>
#include <Engine/Unit/Components/RangeAttackComponent.hpp>
#include <Engine/Unit/Components/RangeComponent.hpp>
#include <Engine/Unit/Components/StrengthComponent.hpp>
#include <Engine/Unit/Components/RangeHealComponent.hpp>

namespace sw::engine
{
	std::shared_ptr<IAction> ActionFactory::createMove(Position targetPosition)
	{
		return std::make_shared<MoveAction>(targetPosition);
	}

	std::shared_ptr<IAction> ActionFactory::createMeleeAttack(std::shared_ptr<IUnit> target, uint32_t damage)
	{
		return std::make_shared<MeleeAttackAction>(target, damage);
	}

	std::shared_ptr<IAction> ActionFactory::createRangeAttack(std::shared_ptr<IUnit> target, uint32_t damage)
	{
		return std::make_shared<RangeAttackAction>(target, damage);
	}

	std::shared_ptr<IAction> ActionFactory::createHeal(std::shared_ptr<IUnit> healer, Map& map, uint32_t spirit)
	{
		auto rangeHealComponent = healer->getComponent<RangeHealComponent>();
		if (rangeHealComponent)
		{
			auto target = map.findRandomUnitInRange(healer, map, rangeHealComponent->getMinRange(), rangeHealComponent->getMaxRange());
			if (target)
			{
				return std::make_shared<HealAction>(target, spirit);
			}
		}
		return nullptr;
	}

	std::shared_ptr<IAction> ActionFactory::createAttack(std::shared_ptr<IUnit> unit, Map& map)
	{
		bool hasMeleeAttack = unit->getComponent<MeleeAttackComponent>() != nullptr;
		if (hasMeleeAttack)
		{
			auto target = map.getRandomAdjacentUnit(unit->getPosition());
			if (target)
			{
				return std::make_shared<MeleeAttackAction>(
					target, unit->getComponent<StrengthComponent>()->getStrength());
			}
		}

		auto rangeAttack = unit->getComponent<RangeAttackComponent>();
		if (rangeAttack)
		{
			auto target = map.findRandomUnitInRange(unit, map, rangeAttack->getMinRange(), rangeAttack->getMaxRange());
			if (target)
			{
				return std::make_shared<RangeAttackAction>(
					target, unit->getComponent<AgilityComponent>()->getAgility());
			}
		}

		return nullptr;
	}
}
