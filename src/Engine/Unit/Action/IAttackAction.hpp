#pragma once
#include <Engine/Unit/IUnit.hpp>
#include "IAction.hpp"

namespace sw::engine
{
	class IAttackAction : public IAction {
	protected:
		std::shared_ptr<IUnit> attackTarget;
		uint32_t damage;

	public:
		IAttackAction(std::shared_ptr<IUnit> target, uint32_t dmg) :
			attackTarget(target),
			damage(dmg) 
		{}
		virtual ~IAttackAction() = default;

		virtual bool execute(std::shared_ptr<IUnit> unit, Map& map) = 0;
		virtual ActionType getType() const override{ return ActionType::AttackAction; }
		
		std::shared_ptr<IUnit> getTarget() { return attackTarget; }
		uint32_t getDamage() const { return damage; }
	};
}
