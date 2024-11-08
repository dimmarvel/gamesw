#pragma once
#include "IUnit.hpp"

namespace sw::engine
{
	/**
	 * @class Swordsman
	 * @brief Represents a Swordsman unit.
	 * 
	 * The `Swordsman` class is derived from `IUnit` and represents a unit specialized in melee combat. 
	 * The Swordsman unit is equipped with a specified amount of health, strength, and the ability to 
	 * perform melee attacks on other units.
	 * 
	 * @see IUnit
	 */
	class Swordsman : public IUnit {
	public:
		Swordsman(size_t id, Position pos, int hp, int strenght);

		/**
		 * @brief Performs an attack on the target unit.
		 * 
		 * This method allows the Swordsman unit to attack a target unit, typically dealing damage 
		 * based on the Swordsman's strength and the target's defense. The target's health is affected 
		 * as a result of the attack.
		 * 
		 * @param target The unit to target with the attack.
		 */
		void attack(IUnit& target);

		/**
		 * @brief Gets the position of the Swordsman unit.
		 * 
		 * This method retrieves the current position of the Swordsman unit on the map.
		 * 
		 * @return The current position of the unit.
		 */
		Position getPosition();
	};
}