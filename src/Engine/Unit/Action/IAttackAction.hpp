#pragma once
#include "IAction.hpp"

#include <Engine/Unit/IUnit.hpp>

namespace sw::engine
{
	/**
	 * @class IAttackAction
	 * @brief Abstract base class for actions that involve attacking.
	 * 
	 * This class serves as a base for all attack actions (both melee and ranged). It encapsulates the 
	 * common behavior of an attack, including the target and the damage dealt. Derived classes should 
	 * implement the specific logic for how the attack is executed (e.g., melee or ranged attack).
	 * 
	 * @see IAction
	 */
	class IAttackAction : public IAction
	{
	protected:
		std::shared_ptr<IUnit> attackTarget;
		uint32_t damage;

	public:
		/**
		 * @brief Constructor for creating an attack action.
		 * 
		 * Initializes the attack action with a target unit and the amount of damage to deal.
		 *
		 * @param target The unit that will be attacked.
		 * @param dmg The amount of damage to deal to the target unit.
		 */
		IAttackAction(std::shared_ptr<IUnit> target, uint32_t dmg) :
				attackTarget(target),
				damage(dmg)
		{}

		virtual ~IAttackAction() = default;

		/**
		 * @brief Executes the attack action.
		 * 
		 * This is a pure virtual function that should be implemented in derived classes. It defines
		 * how the attack is carried out, whether it's a melee or ranged attack, and updates the 
		 * target unit's state accordingly (e.g., reducing health).
		 * 
		 * @param unit The unit performing the attack.
		 * @param map The game map, which may influence the action's outcome (e.g., checking line of sight).
		 * @return `true` if the attack was successfully executed, `false` otherwise.
		 */
		virtual bool execute(std::shared_ptr<IUnit> unit, Map& map) override = 0;

		/**
		 * @brief Gets the type of action (AttackAction).
		 * 
		 * This function overrides the `getType` method from `IAction` and returns the specific action type
		 * for attack actions.
		 *
		 * @return The action type as `ActionType::AttackAction`.
		 */
		virtual ActionType getType() const override
		{
			return ActionType::AttackAction;
		}

		/**
		 * @brief Gets the target unit of the attack.
		 * 
		 * This inline function returns the unit that is the target of the attack.
		 *
		 * @return A shared pointer to the target unit.
		 */
		inline std::shared_ptr<IUnit> getTarget() noexcept
		{
			return attackTarget;
		}

		/**
		 * @brief Gets the damage dealt by the attack.
		 * 
		 * This inline function returns the amount of damage that will be dealt by the attack.
		 *
		 * @return The amount of damage to be dealt.
		 */
		inline uint32_t getDamage() const noexcept
		{
			return damage;
		}
	};
}
