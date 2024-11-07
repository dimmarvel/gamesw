#pragma once
#include "IAction.hpp"

namespace sw::engine
{
	class HealAction : public IAction {
	private:
		int healingAmount;

	public:
		explicit HealAction(int amount) : healingAmount(amount) {}

		ActionType getType() const override { return ActionType::HealingAction; }

		bool execute(std::shared_ptr<IUnit> unit, Map& map) override {
			return true;
		}
	};
}