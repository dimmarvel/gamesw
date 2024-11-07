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

		MovementComponent(int x, int y) :
			currPosition(x, y)
		{}

		void move(int deltaX, int deltaY) 
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
