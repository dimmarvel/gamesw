#include "MoveAction.hpp"

#include <Engine/Unit/IUnit.hpp>
#include "IAction.hpp"
#include <Engine/Core/Map.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/Events/UnitMoved.hpp>

namespace sw::engine
{
	MoveAction::MoveAction(Position target) :
		targetPos(target)
	{}

	bool MoveAction::execute(std::shared_ptr<IUnit> unit, Map& map)
	{
		if(targetPos.getX() >= map.getSizeX() || targetPos.getY() >= map.getSizeY())
			throw std::runtime_error("Target MoveAction out of range");

		Position deltaPos = calcNewPosition(unit, map);
		Position currUnitPos = unit->getPosition();
		Position newPos(
			deltaPos.getX() + currUnitPos.getX(), 
			deltaPos.getY() + currUnitPos.getY()
		);

		map.moveUnit(unit, newPos);
		unit->getComponent<MovementComponent>()->move(deltaPos.getX(), deltaPos.getY());
		EventLog::get().log(io::UnitMoved
		{
			unit->getId(),
			unit->getPosition().getX(),
			unit->getPosition().getY()
		});
		return true;
	}

	Position MoveAction::calcNewPosition(std::shared_ptr<IUnit> unit, const Map& map) const
	{
		if(targetPos.getX() >= map.getSizeX() || targetPos.getY() >= map.getSizeY())
			throw std::runtime_error("Target MoveAction out of range");

		int deltaX = static_cast<int>(targetPos.getX()) - static_cast<int>(unit->getPosition().getX());
		int deltaY = static_cast<int>(targetPos.getY()) - static_cast<int>(unit->getPosition().getY());

		int moveX = 0;
		int moveY = 0;

		if (deltaX != 0)
			moveX = deltaX > 0 ? 1 : -1;

		if (deltaY != 0)
			moveY = deltaY > 0 ? 1 : -1;

		return Position(moveX, moveY);
	}

}
