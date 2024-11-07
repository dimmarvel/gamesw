#pragma once
#include <memory>
#include <Engine/Unit/IUnit.hpp>
#include "IAction.hpp"
#include <unordered_map>
#include <vector>
#include <queue>
#include <stdexcept>
#include <Engine/Unit/Action/ActionFactory.hpp>
#include <algorithm>

namespace sw::engine
{
	class ActionManager {
		using ActionQueue = std::queue<std::shared_ptr<IAction>>;
		using UnitActionsMap = std::unordered_map<std::shared_ptr<IUnit>, ActionQueue>;

	private:
		UnitActionsMap unitActions;
		std::vector<std::shared_ptr<IUnit>> unitOrder;
		size_t currentIndex{0}; 

	public:
		// Register a unit
		void registerUnit(std::shared_ptr<IUnit> unit)
		{
			auto actionIt = unitActions.find(unit);
			if(actionIt != unitActions.end())
				throw std::runtime_error("Unit already registered in ActionManager");
				
			unitActions[unit] = std::queue<std::shared_ptr<IAction>>();
			unitOrder.push_back(unit);
		}

		// Add an action for a specific unit
		void addAction(std::shared_ptr<IUnit> unit, std::shared_ptr<IAction> action)
		{
			auto unitIt = unitActions.find(unit);
			if(unitIt == unitActions.end())
				throw std::runtime_error("Unit has not been registered");

			unitActions[unit].push(action);
		}

		// Process one action per unit in round-robin order
		void processActions(Map& map)
		{
			do
			{
				if (unitOrder.empty())
					return;

				std::shared_ptr<IUnit> unit = unitOrder[currentIndex];

				if (!unitActions[unit].empty())
				{
					auto action = unitActions[unit].front();
					handleAction(unit, map, action);
				}

				incrementNextUnit();
			} while (currentIndex != 0);
		}

		bool isAllActionsCompleted() const
		{
			for (const auto& [unit, actions] : unitActions) {
				if (!actions.empty()) return false;
			}
			return true;
		}


		bool removeUnit(std::shared_ptr<IUnit> unit)
		{
			return std::erase(unitOrder, unit) > 0;
		}

	private:
		// Move to the next unit for the next tick
		void incrementNextUnit()
		{
			currentIndex = (currentIndex + 1) % unitOrder.size();
		}
		
		void handleAction(std::shared_ptr<IUnit> unit, Map& map, std::shared_ptr<IAction> action)
		{
				if(action->getType() == ActionType::MoveAction)
				{
					if(handleAttack(unit, map))
						return;

					auto moveAction = std::static_pointer_cast<MoveAction>(action);
					if(handleMove(unit, map, moveAction))
						return;
				}

		}

		bool handleAttack(std::shared_ptr<IUnit> unit, Map& map)
		{
			auto attackAction = ActionFactory::createAttack(unit, map);
			if(attackAction)
			{
				if(attackAction->execute(unit, map))
				{
					return true;
				}
			}
			return false;
		}
		
		bool handleMove(std::shared_ptr<IUnit> unit, Map& map, std::shared_ptr<MoveAction> moveAction)
		{
			if (moveAction->execute(unit, map))
			{
				if(unit->getPosition() == moveAction->getTargetPosition())
					unitActions[unit].pop();
				return true;
			}
			return false;
		}
	};
}