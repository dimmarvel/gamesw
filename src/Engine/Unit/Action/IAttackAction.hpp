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
		ActionType getType() const = 0;
		std::shared_ptr<IUnit> getTarget() { return attackTarget; }
		uint32_t getDamage() const { return damage; }
	};
}
