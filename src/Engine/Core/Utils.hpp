#pragma once
#include <Engine/Unit/Action/IAction.hpp>
#include <string>

namespace sw::engine::utils
{
	inline std::string to_string(ActionType action)
	{
		switch (action)
		{
			case ActionType::AttackAction: return "AttackAction";
			case ActionType::MeleeAttackAction: return "MeleeAttackAction";
			case ActionType::RangeAttackAction: return "RangeAttackAction";
			case ActionType::MoveAction: return "MoveAction";
			case ActionType::HealingAction: return "HealingAction";
			case ActionType::UnknownAction: return "UnknownAction";
			default: throw std::invalid_argument("Bad to string ActionType");
		}
	}
}
