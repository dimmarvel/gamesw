#pragma once
#include "IUnit.hpp"

namespace sw::engine
{

	/**
	 * @class Hunter
	 * @brief Represents a Hunter unit.
	 * 
	 * The `Hunter` class is derived from `IUnit` and represents a unit with specific attributes 
	 * like health, agility, strength, and range. The Hunter unit has the ability to perform both 
	 * ranged and melee attacks, as well as calculate the damage dealt during a melee attack.
	 * 
	 * @see IUnit
	 */
	class Hunter : public IUnit {
	public:
		Hunter(size_t id, Position pos, int health, int agility, int strenght, int range);

		/**
		 * @brief Calculates the damage dealt by a melee attack.
		 * 
		 * This method calculates the damage of a melee attack based on the Hunter's strength and 
		 * other relevant factors (e.g., weapon, buffs, etc.).
		 * 
		 * @return The amount of damage dealt in a melee attack.
		 */
		uint32_t meleeDamage();
		
		Position getPosition();
		/**
		 * @brief Performs a ranged attack on the target unit.
		 * 
		 * This method allows the Hunter unit to perform a ranged attack on a specified target unit.
		 * The target unit's health and other states may be affected depending on the attack's outcome.
		 * 
		 * @param target The unit to target with the ranged attack.
		 */
		void rangeAttack(IUnit& target);

		/**
		 * @brief Performs a melee attack on the target unit.
		 * 
		 * This method allows the Hunter unit to perform a melee attack on a specified target unit.
		 * The target unit's health and other states may be affected depending on the attack's outcome.
		 * 
		 * @param target The unit to target with the melee attack.
		 */
		void meleeAttack(IUnit& target);
	};
}