#pragma once

#include "IComponent.hpp"
#include <Engine/Unit/IUnit.hpp>
#include <memory>

namespace sw::engine
{
	class GameObserver;

	class HPComponent : public IComponent 
	{
	public:
		int health;

		explicit HPComponent(int hp) : health(hp) {}

		bool processUnitDeath(unitId id, std::shared_ptr<GameObserver> gObserver);
		void takeDamage(int damage);
		bool isAlive();
	};
}
