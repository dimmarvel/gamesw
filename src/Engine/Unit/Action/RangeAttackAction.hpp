#pragma once
#include "IAttackAction.hpp"

namespace sw::engine
{
	class Map;

	class RangeAttackAction final : public IAttackAction {
	public:
		explicit RangeAttackAction(std::shared_ptr<IUnit> target, uint32_t dmg);

		virtual ActionType getType() const override { return ActionType::RangeAttackAction; }
		virtual bool execute(std::shared_ptr<IUnit> attackerUnit, Map& map) override;
	};
}