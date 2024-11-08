#pragma once
#include "IComponent.hpp"
#include <Engine/Unit/IUnit.hpp>
#include <Engine/Core/Position.hpp>
#include <memory>

namespace sw::engine
{
	/**
	 * @class MovementComponent
	 * @brief Component that manages the movement and position of a unit.
	 * 
	 * The `MovementComponent` class handles the position and movement functionality for a unit.
	 * It tracks the current position of the unit and whether the unit is allowed to move.
	 * The component allows updating the unit's position and checking if it is movable.
	 */
	class MovementComponent final : public IComponent 
	{
	private:
		Position currPosition;
		bool movable{true};

	public:
		/**
		 * @brief Constructs a `MovementComponent` with the specified position and movement capability.
		 * 
		 * @param pos The initial position of the unit.
		 * @param canMove Boolean flag indicating if the unit can move. Default is `true`.
		 */
		MovementComponent(const Position& pos, bool canMove = true) :
			currPosition(pos),
			movable(canMove)
		{}

		/**
		 * @brief Constructs a `MovementComponent` with the specified x and y coordinates and movement capability.
		 * 
		 * @param x The x-coordinate of the initial position.
		 * @param y The y-coordinate of the initial position.
		 * @param canMove Boolean flag indicating if the unit can move. Default is `true`.
		 */
		MovementComponent(int x, int y, bool canMove = true) :
			currPosition(x, y)
		{}

		/**
		 * @brief Moves the unit by the specified deltas.
		 * 
		 * This method updates the current position of the unit by the provided deltas in both the x and y directions.
		 * 
		 * @param deltaX The change in the x-coordinate.
		 * @param deltaY The change in the y-coordinate.
		 */
		void move(int deltaX, int deltaY) { currPosition.move(deltaX, deltaY); }

		inline Position getPosition() const noexcept{ return currPosition; }
		inline bool isMovable() const noexcept{ return movable; }

	};
}
