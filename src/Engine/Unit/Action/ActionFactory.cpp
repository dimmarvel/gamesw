#include "ActionFactory.hpp"

#include "MoveAction.hpp"
#include "MeleeAttackAction.hpp"
#include "RangeAttackAction.hpp"

#include <Engine/Map.hpp>
#include <Engine/Position.hpp>
#include <Engine/Unit/Components/StrengthComponent.hpp>
#include <Engine/Unit/Components/AgilityComponent.hpp>
#include <Engine/Unit/Components/RangeComponent.hpp>
#include <Engine/Unit/Components/RangeAttackComponent.hpp>
#include <Engine/Unit/Components/MeleeAttackComponent.hpp>

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

	std::shared_ptr<IAction> ActionFactory::createAttack(std::shared_ptr<IUnit> unit, Map& map)
	{
		bool hasRangeAttack = unit->getComponent<RangeAttackComponent>() != nullptr;
		bool hasMeleeAttack = unit->getComponent<MeleeAttackComponent>() != nullptr;

		if (hasMeleeAttack)
		{
			auto target = map.getRandomAdjacentUnit(unit->getPosition());
			if (target)
				return std::make_shared<MeleeAttackAction>(target, unit->getComponent<StrengthComponent>()->getStrength());
		}

		if (hasRangeAttack)
		{
			auto target = map.findUnitInRange(unit, map, 2, unit->getComponent<RangeComponent>()->getRange());
			if (target)
				return std::make_shared<RangeAttackAction>(target, unit->getComponent<AgilityComponent>()->getAgility());
		}

		return nullptr;
	}
}