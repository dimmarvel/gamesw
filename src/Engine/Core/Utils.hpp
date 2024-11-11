#pragma once
#include <Engine/Unit/Action/IAction.hpp>
#include <string>
#include <random>

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

	static std::mt19937& getGenerator()
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());
		return gen;
	}

	static size_t getRandom(size_t min, size_t max)
	{
		std::uniform_int_distribution<size_t> dist(min, max);
		return dist(getGenerator());
	}
}
