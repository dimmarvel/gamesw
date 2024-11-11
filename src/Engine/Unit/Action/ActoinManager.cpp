#include "ActoinManager.hpp"

#include "IAction.hpp"

#include <Engine/Unit/Action/ActionFactory.hpp>
#include <Engine/Unit/Action/MoveAction.hpp>
#include <Engine/Unit/IUnit.hpp>
#include <Engine/Unit/Components/HealingComponent.hpp>

namespace sw::engine
{
	void ActionManager::registerUnit(std::shared_ptr<IUnit> unit)
	{
		auto actionIt = unitActions.find(unit);
		if (actionIt != unitActions.end())
		{
			throw std::runtime_error("Unit already registered in ActionManager");
		}

		unitActions[unit] = std::queue<std::shared_ptr<IAction>>();
		unitOrder.push_back(unit);
	}

	void ActionManager::addAction(std::shared_ptr<IUnit> unit, std::shared_ptr<IAction> action)
	{
		auto unitIt = unitActions.find(unit);
		if (unitIt == unitActions.end())
		{
			throw std::runtime_error("Unit " + std::to_string(unit->getId()) +" has not been registered");
		}

		unitActions[unit].push(action);
	}

	void ActionManager::processActions(Map& map)
	{
		do
		{
			if (unitOrder.empty())
			{
				return;
			}

			std::shared_ptr<IUnit> unit = unitOrder[currentIndex];

			if (!unitActions[unit].empty())
			{
				auto action = unitActions[unit].front();
				handleAction(unit, map, action);
			}

			incrementNextUnit();
		}
		while (currentIndex != 0);
	}

	bool ActionManager::isAllActionsCompleted() const
	{
		for (const auto& [unit, actions] : unitActions)
		{
			if (!actions.empty())
			{
				return false;
			}
		}
		return true;
	}

	bool ActionManager::removeUnit(std::shared_ptr<IUnit> unit)
	{
		unitActions.erase(unit);
		return std::erase(unitOrder, unit) > 0 && unitActions.count(unit) == 0;
	}

	void ActionManager::incrementNextUnit()
	{
		currentIndex = (currentIndex + 1) % unitOrder.size();
	}

	void ActionManager::handleAction(std::shared_ptr<IUnit> unit, Map& map, std::shared_ptr<IAction> action)
	{
		switch(unit->getType())
		{
			case UnitType::Hunter:
			{
				if(handleAttack(unit, map))
					return;
				break;
			}
			case UnitType::Swordsman:
			{
				if(handleAttack(unit, map))
					return;
				break;
			}
			case UnitType::Heal:
			{
				if(handleHealing(unit, map))
					return;
				break;
			}
			default:
				std::runtime_error("Handle unknown action");
		}

		handleMove(unit, map, action);
	}

	bool ActionManager::handleHealing(std::shared_ptr<IUnit> unit, Map& map)
	{
		auto healComponent = unit->getComponent<HealingComponent>();
		if(!healComponent)
			return false;

		auto healingAction = ActionFactory::createHeal(unit, map, healComponent->getSpirit());
		if(!healingAction)
			return false;

		if (healingAction->execute(unit, map))
		{
			return true;
		}

		return false;
	}

	bool ActionManager::handleAttack(std::shared_ptr<IUnit> unit, Map& map)
	{
		auto attackAction = ActionFactory::createAttack(unit, map);
		if (!attackAction)
			return false;

		if (attackAction->execute(unit, map))
			return true;
		return false;
	}

	bool ActionManager::handleMove(std::shared_ptr<IUnit> unit, Map& map, std::shared_ptr<IAction> action)
	{
		auto moveAction = std::dynamic_pointer_cast<MoveAction>(action);
		if(!moveAction)
			return false;

		if (moveAction->execute(unit, map))
		{
			if (unit->getPosition() == moveAction->getTargetPosition())
			{
				unitActions[unit].pop();
			}
			return true;
		}
		return false;
	}
}
