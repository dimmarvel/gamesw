#pragma once
#include "IAttackAction.hpp"

namespace sw::engine
{
	class Map;

	class MeleeAttackAction : public IAttackAction
	{
	public:
		explicit MeleeAttackAction(std::shared_ptr<IUnit> target, uint32_t dmg);

		virtual ActionType getType() const override { return ActionType::MeleeAttackAction; }

		virtual bool execute(std::shared_ptr<IUnit> attackerUnit, Map& map) override;
	};
}