#include <memory>
#include <Engine/Unit/IUnit.hpp>
#include "IAction.hpp"
#include <unordered_map>
#include <vector>
#include <queue>
#include <stdexcept>

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
		// Register a unit with ActionManager
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
		void processActions(Map& map) {
			if (unitOrder.empty()) 
				return;

			std::shared_ptr<IUnit> unit = unitOrder[currentIndex];

			if (!unitActions[unit].empty())
			{
				auto action = unitActions[unit].front();
				unitActions[unit].pop();
				if(action)
				action->execute(unit, map);
			}

			// Move to the next unit for the next tick
			currentIndex = (currentIndex + 1) % unitOrder.size();
		}

		bool isAllActionsCompleted() const {
			for (const auto& [unit, actions] : unitActions) {
				if (!actions.empty()) return false;
			}
			return true;
		}
	};
}