#pragma once
#include <Engine/Unit/IUnit.hpp>

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

	class IAction 
	{
	public:
		virtual bool execute(std::shared_ptr<IUnit> unit, Map& map) = 0;
		virtual ActionType getType() const = 0;
		virtual ~IAction() = default;
	};
}
