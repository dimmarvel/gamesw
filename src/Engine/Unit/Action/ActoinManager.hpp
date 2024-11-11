#pragma once
#include <algorithm>
#include <memory>
#include <queue>
#include <unordered_map>
#include <vector>

namespace sw::engine
{
	class IAction;
	class IUnit;
	class Map;
	class MoveAction;

	/**
	 * @class ActionManager
	 * @brief Manages and processes actions for units in a game.
	 * 
	 * The ActionManager class is responsible for managing actions for units
	 * in a round-robin order. It maintains a queue of actions for each unit,
	 * allowing each unit to execute actions in sequence. It also facilitates 
	 * the addition, removal, and processing of actions for each unit.
	 */
	class ActionManager final
	{
		using ActionQueue = std::queue<std::shared_ptr<IAction>>;
		using UnitActionsMap = std::unordered_map<std::shared_ptr<IUnit>, ActionQueue>;

	private:
		UnitActionsMap unitActions;
		std::vector<std::shared_ptr<IUnit>> unitOrder;
		size_t currentIndex{0};

	public:
		/**
		 * @brief Registers a unit to the ActionManager.
		 * @param unit The unit to register.
		 * @throws std::runtime_error if the unit is already registered.
		 */
		void registerUnit(std::shared_ptr<IUnit> unit);

		/**
		 * @brief Adds an action to a unit's action queue.
		 * @param unit The unit to add the action for.
		 * @param action The action to add.
		 * @throws std::runtime_error if the unit is not registered.
		 */
		void addAction(std::shared_ptr<IUnit> unit, std::shared_ptr<IAction> action);

		/**
		 * @brief Processes one action for each unit in round-robin order.
		 * @param map The game map on which actions are executed.
		 * 
		 * Each unit takes turns executing its queued actions until all units
		 * have processed an action.
		 */
		void processActions(Map& map);

		/**
		 * @brief Checks if all units have completed their actions.
		 * @return True if all actions are completed, false otherwise.
		 */
		bool isAllActionsCompleted() const;

		/**
		 * @brief Removes a unit and its associated actions from the ActionManager.
		 * @param unit The unit to remove.
		 * @return True if the unit was removed, false if the unit was not found.
		 */
		bool removeUnit(std::shared_ptr<IUnit> unit);

	private:
		/**
		 * @brief Advances to the next unit in the round-robin order.
		 * 
		 * This method increments the currentIndex to point to the next unit,
		 * wrapping around to the beginning of the unit list if needed.
		 */
		void incrementNextUnit();

		/**
		 * @brief Handles the execution of a unit's action.
		 * @param unit The unit performing the action.
		 * @param map The game map on which the action is executed.
		 * @param action The action to execute.
		 * 
		 * This function checks the action type and delegates handling to
		 * specific methods such as `handleMove` or `handleAttack`.
		 */
		void handleAction(std::shared_ptr<IUnit> unit, Map& map, std::shared_ptr<IAction> action);

		bool handleHealing(std::shared_ptr<IUnit> unit, Map& map);

		/**
		 * @brief Attempts to execute an attack action for a unit.
		 * @param unit The unit attempting the attack.
		 * @param map The game map on which the attack is executed.
		 * @return True if the attack action was executed, false otherwise.
		 * 
		 * If an attack is possible, this function executes the attack and returns true.
		 * If no attack can be performed, it returns false.
		 */
		bool handleAttack(std::shared_ptr<IUnit> unit, Map& map);

		/**
		 * @brief Attempts to execute a move action for a unit.
		 * @param unit The unit attempting to move.
		 * @param map The game map on which the move is executed.
		 * @param action The move action to execute.
		 * @return True if the move action was successful, false otherwise.
		 * 
		 * This function executes the move action. If the unit reaches its target position,
		 * the action is removed from the unit's action queue.
		 */
		bool handleMove(std::shared_ptr<IUnit> unit, Map& map, std::shared_ptr<IAction> action);
	};
}
