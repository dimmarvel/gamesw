#pragma once

#include "IComponent.hpp"
#include <Engine/Unit/IUnit.hpp>
#include <memory>

namespace sw::engine
{
	class GameObserver;

	/**
	 * @class HealthComponent
	 * @brief Represents the health component of a unit.
	 * 
	 * This class is responsible for managing the health of a unit. It tracks the unit's health, 
	 * allows the unit to take damage, and checks if the unit is still alive. Additionally, it processes 
	 * the unit's death and can notify the game observer when the unit dies.
	 * 
	 * @see IComponent
	 */
	class HealthComponent final : public IComponent 
	{
	private:
		int health;

	public:
		explicit HealthComponent(int hp);

		/**
		 * @brief Processes unit death.
		 * 
		 * This method checks if the unit is dead and, if so, notifies the game observer about the death.
		 * 
		 * @param id The unit's unique ID.
		 * @param gObserver The game observer that listens for changes in unit states.
		 * @return `true` if the unit has died, `false` otherwise.
		 */
		bool processUnitDeath(unitId id, std::shared_ptr<GameObserver> gObserver);

		/**
		 * @brief Applies damage to the unit.
		 * 
		 * This method decreases the unit's health by the specified damage value. If the health reaches 
		 * zero or below, the unit is considered dead.
		 * 
		 * @param damage The amount of damage to apply to the unit's health.
		 */
		void takeDamage(int damage);

		/**
		 * @brief Checks if the unit is still alive.
		 * 
		 * This method returns whether the unit has positive health (i.e., it is alive).
		 * 
		 * @return `true` if the unit is alive (health > 0), `false` otherwise.
		 */
		bool isAlive();

		inline int getHealth() const noexcept{ return health; }
	};
}
