#pragma once
#include <memory>
#include "MoveAction.hpp"
#include <Engine/Position.hpp>

namespace sw::engine
{
	class ActionFactory 
	{
	public:
		static std::shared_ptr<IAction> createMove(Position targetPosition) {
			return std::make_shared<MoveAction>(targetPosition);
		}

	};
}