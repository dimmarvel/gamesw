#pragma once
#include <Engine/Unit/IUnit.hpp>
#include "IAction.hpp"
#include "IAttackAction.hpp"
#include <iostream>
#include <Engine/Unit/Components/HPComponents.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/Events/UnitAttacked.hpp>

namespace sw::engine
{
	class MeleeAttackAction : public IAttackAction {
	public:
		explicit MeleeAttackAction(std::shared_ptr<IUnit> target, uint32_t dmg) :
			IAttackAction(target, dmg)
		{}

		ActionType getType() const override { return ActionType::MeleeAttackAction; }

		bool execute(std::shared_ptr<IUnit> attackerUnit, Map& map) override
		{
			auto hpComponent = attackTarget->getComponent<HPComponent>();
			hpComponent->takeDamage(damage);

			EventLog::get().log(io::UnitAttacked
			{
				attackerUnit->getId(),
				attackTarget->getId(),
				damage,
				static_cast<uint32_t>(hpComponent->health)
			});
			return true;
		}
	};
}