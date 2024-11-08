#include "IUnit.hpp"

#include <Engine/Position.hpp>

namespace sw::engine
{
	bool IUnit::isMovable()
	{
		auto movement = getComponent<MovementComponent>();
		if(movement)
			if(movement->isMovable())
				return true;
		return false;
	}

	Position IUnit::getPosition()
	{
		if(!isMovable())
			throw std::runtime_error("Call move in nonmovable unit");
		return getComponent<MovementComponent>()->getPosition();
	}
}