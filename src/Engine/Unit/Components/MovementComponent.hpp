#pragma once
#include "IComponent.hpp"
#include <Engine/Unit/IUnit.hpp>
#include <Engine/Position.hpp>
#include <memory>

namespace sw::engine
{
	class MovementComponent : public IComponent 
	{
	private:
		Position currPosition;
		bool movable{true};

	public:
		MovementComponent(const Position& pos, bool canMove = true) :
			currPosition(pos),
			movable(canMove)
		{}

		MovementComponent(uint32_t x, uint32_t y) :
			currPosition(x, y)
		{}

		void move(uint32_t deltaX, uint32_t deltaY) 
		{
			currPosition.move(deltaX, deltaY);
		}

		Position getPosition()
		{
			return currPosition;
		}

		bool isMovable()
		{
			return movable;
		}

	};
}
