#pragma once
#include <Engine/Unit/IUnit.hpp>
#include "IAction.hpp"
#include <iostream>

namespace sw::engine
{
	class RangeAttackAction : public IAction {
	private:
		int damage;

	public:
		explicit RangeAttackAction(int dmg) : damage(dmg) {}

		void execute(std::shared_ptr<IUnit> unit, Map& map) override {
			std::cout << "Attacking unit: " << targetUnit->getId() << " for " << damage << " damage.\n";
		}
	};
}