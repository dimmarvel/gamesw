#pragma once
#include <Engine/Unit/IUnit.hpp>
#include <stdexcept>

namespace sw::engine
{
	class Map;

	enum class ActionType
	{
		AttackAction,
		MeleeAttackAction,
		RangeAttackAction,
		MoveAction,
		HealingAction,
		UnknownAction
	};

	/**
	 * @class IAction
	 * @brief An interface for actions that a unit can perform.
	 * 
	 * This interface defines the essential methods that any action (such as attack, move, heal) must implement.
	 * It allows for polymorphic behavior, enabling units to perform various types of actions without needing 
	 * to know the specifics of each action type.
	 */
	class IAction
	{
	public:
		/**
		 * @brief Executes the action for a given unit.
		 * This pure virtual function defines the general behavior of an action. Each derived action class
		 * will implement the specific behavior of the action when executed.
		 * @param unit The unit that performs the action.
		 * @param map The game map, used to determine the action's effects within the game world.
		 * @return `true` if the action was successfully executed, `false` otherwise.
		 */
		virtual bool execute(std::shared_ptr<IUnit> unit, Map& map) = 0;

		/**
		 * @brief Retrieves the type of the action.
		 * This function returns the `ActionType` of the action, which helps to identify the specific action 
		 * and allows other parts of the game (like the Action Manager) to handle it accordingly.
		 * @return The type of the action as an `ActionType` enum value.
		 */
		virtual ActionType getType() const = 0;

		/**
		 * @brief Virtual destructor for IAction.
		 * The virtual destructor ensures that derived class destructors are called properly when deleting
		 * an instance of a derived class through a pointer to IAction.
		 */
		virtual ~IAction() = default;
	};
}
