#pragma once
#include <memory>

namespace sw::engine
{
	class IUnit;
	class Position;
	class IAction;
	class Map;

	/**
	 * @class ActionFactory
	 * @brief Factory for creating various types of actions for game units.
	 * 
	 * ActionFactory provides static methods to create different actions such as
	 * movement, melee attack, and range attack. Additionally, it determines if
	 * a unit can perform an attack action based on its components and the current
	 * game state.
	 */
	class ActionFactory 
	{
	public:
		/**
		 * @brief Creates a move action toward a specified target position.
		 * @param targetPosition The position the unit should move to.
		 * @return A shared pointer to the created MoveAction.
		 */
		static std::shared_ptr<IAction> createMove(Position targetPosition);

		/**
		 * @brief Creates a melee attack action targeting a specified unit.
		 * @param target The target unit for the melee attack.
		 * @param damage The damage to be dealt by the attack.
		 * @return A shared pointer to the created MeleeAttackAction.
		 */
		static std::shared_ptr<IAction> createMeleeAttack(std::shared_ptr<IUnit> target, uint32_t damage);

		/**
		 * @brief Creates a range attack action targeting a specified unit.
		 * @param target The target unit for the range attack.
		 * @param damage The damage to be dealt by the attack.
		 * @return A shared pointer to the created RangeAttackAction.
		 */
		static std::shared_ptr<IAction> createRangeAttack(std::shared_ptr<IUnit> target, uint32_t damage);

		/**
		 * @brief Creates an attack action for a unit based on its attack capabilities.
		 * @param unit The unit attempting to perform an attack.
		 * @param map The game map containing information about other units.
		 * @return A shared pointer to the created attack action if one is possible,
		 * or nullptr if no valid attack can be performed.
		 * 
		 * This method first checks if the unit has melee attack capabilities.
		 * If a valid melee target is adjacent, it creates a MeleeAttackAction.
		 * If not, it checks if the unit has range attack capabilities and can
		 * find a target within range, creating a RangeAttackAction if so.
		 */
		static std::shared_ptr<IAction> createAttack(std::shared_ptr<IUnit> unit, Map& map);
	};
}