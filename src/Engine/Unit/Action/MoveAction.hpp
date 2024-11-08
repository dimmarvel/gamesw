#pragma once
#include "IAction.hpp"
#include <Engine/Core/Position.hpp>

namespace sw::engine
{
	class Map;
	class IUnit;

	/**
	 * @class MoveAction
	 * @brief Represents a move action for a unit.
	 * 
	 * This class implements the `IAction` interface to define the logic for moving a unit 
	 * to a specified target position on the map. The movement is based on the unit's position 
	 * and the provided target position. Derived classes can override behavior if necessary.
	 * 
	 * @see IAction
	 */
	class MoveAction final : public IAction
	{
	private:
		Position targetPos;

	public:
		MoveAction(Position target);
		virtual ~MoveAction() = default;

		virtual ActionType getType() const override { return ActionType::MoveAction; }

		/**
		 * @brief Executes the move action.
		 * 
		 * This method moves the unit to the specified target position if possible. The actual movement
		 * depends on the unit's movement capabilities and any obstacles on the map.
		 * 
		 * @param unit The unit performing the move action.
		 * @param map The game map, which contains the information needed to move the unit (e.g., obstacles).
		 * @return `true` if the move was successful, `false` otherwise.
		 */
		virtual bool execute(std::shared_ptr<IUnit> unit, Map& map) override;

		/**
		 * @brief Gets the target position of the move action.
		 * 
		 * This inline function returns the position to which the unit will move.
		 *
		 * @return The target position of the move action.
		 */
		inline Position getTargetPosition() const noexcept { return targetPos; }

	private:
		/**
		 * @brief Calculates the new position for the unit after the move.
		 * 
		 * This helper function calculates the new position for the unit based on its current position 
		 * and the map's layout. It ensures that the move is valid and respects any constraints (e.g., 
		 * avoiding obstacles).
		 *
		 * @param unit The unit performing the move.
		 * @param map The game map, which is used to determine the new position.
		 * @return The new position after the move.
		 */
		Position calcNewPosition(std::shared_ptr<IUnit> unit, const Map& map) const;
	};
}