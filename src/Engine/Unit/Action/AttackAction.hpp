#pragma once
#include <Engine/Unit/IUnit.hpp>
#include "IAction.hpp"
#include <iostream>

namespace sw::engine
{
	class MeeleAttackAction : public IAction {
	private:
		int damage;

	public:
		explicit MeeleAttackAction(int dmg) : damage(dmg) {}

		void execute(std::shared_ptr<IUnit> unit, Map& map) override {
			std::cout << "Attacking unit: " << targetUnit->getId() << " for " << damage << " damage.\n";
		}
	};
}