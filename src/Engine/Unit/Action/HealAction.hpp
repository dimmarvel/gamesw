#pragma once
#include "IAction.hpp"
#include <iostream>

namespace sw::engine
{
	class HealAction : public IAction {
	private:
		int healingAmount;

	public:
		explicit HealAction(int amount) : healingAmount(amount) {}

		void execute(std::shared_ptr<IUnit> unit, Map& map) override {
			std::cout << "Healing unit: " << targetUnit->getId() << " for " << healingAmount << " HP.\n";
		}
	};
}