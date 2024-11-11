#pragma once
#include "IAction.hpp"

namespace sw::engine
{
	class Map;

	/**
	 * @class HealAction
	 * @brief Represents a healing action performed by a unit.
	 *
	 * The HealAction is responsible for restoring health to a target unit using 
	 * the healer's spiritual power. This action interacts with the target's 
	 * HealthComponent to apply healing and logs the event.
	 */
	class HealAction final : public IAction
	{
		std::shared_ptr<IUnit> healingTarget;
		uint32_t spirit;
	public:
		explicit HealAction(std::shared_ptr<IUnit> target, uint32_t sp);

		virtual ActionType getType() const override;
		/**
		 * @brief Executes the healing action.
		 *
		 * Restores health to the target unit using the specified amount of spiritual power.
		 * Updates the target's HealthComponent and logs the healing event.
		 *
		 * @param healerUnit The unit performing the healing action.
		 * @param map The game map (not directly used in this action).
		 * @return True if the action was successfully executed.
		 */
		virtual bool execute(std::shared_ptr<IUnit> healerUnit, Map& map) override;
	};
}
