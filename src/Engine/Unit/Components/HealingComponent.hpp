#pragma once

#include "IComponent.hpp"

#include <Engine/Unit/IUnit.hpp>
#include <memory>

namespace sw::engine
{
	class GameObserver;

	/**
	 * @class HealingComponent
	 * @brief Represents a healing capability of a unit.
	 *
	 * The HealingComponent provides the ability to heal other units. It holds
	 * the amount of spiritual power (spirit) the unit can use for healing.
	 */
	class HealingComponent final : public IComponent
	{
	private:
		int spirit;

	public:
		explicit HealingComponent(int sp) : spirit(sp) {}

		inline int getSpirit() const noexcept
		{
			return spirit;
		}
	};
}
