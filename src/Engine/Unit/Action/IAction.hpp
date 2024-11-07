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

	inline std::string to_string(ActionType action) 
	{
		switch (action) {
			case ActionType::AttackAction:
				return "AttackAction";
			case ActionType::MeleeAttackAction:
				return "MeleeAttackAction";
			case ActionType::RangeAttackAction:
				return "RangeAttackAction";
			case ActionType::MoveAction:
				return "MoveAction";
			case ActionType::HealingAction:
				return "HealingAction";
			case ActionType::UnknownAction:
				return "UnknownAction";
			default:
				throw std::invalid_argument("Bad to string ActionType");
		}
	}

	class IAction 
	{
	public:
		virtual bool execute(std::shared_ptr<IUnit> unit, Map& map) = 0;
		virtual ActionType getType() const = 0;
		virtual ~IAction() = default;
	};
}
