#pragma once
#include <memory>
#include "MoveAction.hpp"
#include "MeleeAttackAction.hpp"
#include "RangeAttackAction.hpp"
#include <Engine/Position.hpp>
#include <Engine/Unit/Components/StrengthComponent.hpp>
#include <Engine/Unit/Components/AgilityComponent.hpp>
#include <Engine/Unit/Components/RangeComponent.hpp>
#include <Engine/Unit/Components/RangeAttackComponent.hpp>
#include <Engine/Unit/Components/MeleeAttackComponent.hpp>

namespace sw::engine
{
	class ActionFactory 
	{
	public:
		static std::shared_ptr<IAction> createMove(Position targetPosition) {
			return std::make_shared<MoveAction>(targetPosition);
		}

		static std::shared_ptr<IAction> createMeleeAttack(std::shared_ptr<IUnit> target, uint32_t damage) {
			return std::make_shared<MeleeAttackAction>(target, damage);
		}

		static std::shared_ptr<IAction> createRangeAttack(std::shared_ptr<IUnit> target, uint32_t damage) {
			return std::make_shared<RangeAttackAction>(target, damage);
		}

		// Return nullptr if cant attack, retrun Attack action if attack is real
		static std::shared_ptr<IAction> createAttack(std::shared_ptr<IUnit> unit, Map& map) {
			bool hasRangeAttack = unit->getComponent<RangeAttackComponent>() != nullptr;
			bool hasMeleeAttack = unit->getComponent<MeleeAttackComponent>() != nullptr;

			if (hasMeleeAttack)
			{
				auto target = map.getRandomAdjacentUnit(unit->getPosition());
				if (target)
					return std::make_shared<MeleeAttackAction>(target, unit->getComponent<StrengthComponent>()->strength);
			}
			
			if (hasRangeAttack)
			{
				auto target = map.findUnitInRange(unit, map, 2, unit->getComponent<RangeComponent>()->range);
				if (target)
					return std::make_shared<RangeAttackAction>(target, unit->getComponent<AgilityComponent>()->agility);
			}

			return nullptr;
		}
	};
}