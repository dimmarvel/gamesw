#pragma once
#include <Engine/Unit/IUnit.hpp>
#include "IAction.hpp"
#include <Engine/Unit/Components/HPComponents.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/Events/UnitAttacked.hpp>
namespace sw::engine
{
	class RangeAttackAction : public IAction {
	private:
		uint32_t damage;
		std::shared_ptr<IUnit> attackTarget;

	public:
		explicit RangeAttackAction(std::shared_ptr<IUnit> target, uint32_t dmg) :
			attackTarget(target),
			damage(dmg)
		{}
		ActionType getType() const override { return ActionType::RangeAttackAction; }

		bool execute(std::shared_ptr<IUnit> attackerUnit, Map& map) override 
		{
			//TODO: Check range for attack, create validation method

			auto hpComponent = attackTarget->getComponent<HPComponent>();
			hpComponent->takeDamage(damage);

			EventLog::get().log(io::UnitAttacked
			{
				attackerUnit->getId(),
				attackTarget->getId(),
				damage,
				static_cast<uint32_t>(hpComponent->health)
			});

			EventLog::get().log(io::UnitAttacked{attackerUnit->getId(), attackTarget->getId(), damage, hpComponent->health});
			return true;
		}
	};
}