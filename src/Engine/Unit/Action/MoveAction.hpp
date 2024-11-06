#pragma once
#include <Engine/Unit/IUnit.hpp>
#include "IAction.hpp"
#include <iostream>
#include <Engine/Map.hpp>

namespace sw::engine
{
	class MoveAction : public IAction {
	private:
		Position target;

	public:
		MoveAction(Position target) : target(target) {}

		ActionType getType() const override { return ActionType::MoveAction; }

		bool execute(std::shared_ptr<IUnit> unit, Map& map) override 
		{
			if(target.getX() >= map.getSizeX() || target.getY() >= map.getSizeY())
				throw std::runtime_error("Target MoveAction out of range");

			Position deltaPos = calcNewPosition(unit, map);
			Position currUnitPos = unit->getPosition();
			Position newPos(
				deltaPos.getX() + currUnitPos.getX(), 
				deltaPos.getY() + currUnitPos.getY()
			);

			map.moveUnit(unit, newPos);
			unit->move(deltaPos.getX(), deltaPos.getY());
			EventLog::get().log(io::UnitMoved{unit->getId(), unit->getPosition().getX(), unit->getPosition().getY()});
			return true;
		}

	private:
		Position calcNewPosition(std::shared_ptr<IUnit> unit, const Map& map) const
		{
			if(target.getX() >= map.getSizeX() || target.getY() >= map.getSizeY())
				throw std::runtime_error("Target MoveAction out of range");

			int deltaX = static_cast<int>(target.getX()) - static_cast<int>(unit->getPosition().getX());
			int deltaY = static_cast<int>(target.getY()) - static_cast<int>(unit->getPosition().getY());

			int moveX = 0;
			int moveY = 0;

			if (deltaX != 0) {
				moveX = deltaX > 0 ? 1 : -1;
			}

			if (deltaY != 0) {
				moveY = deltaY > 0 ? 1 : -1;
			}
			return Position(moveX, moveY);
		}

	};
}