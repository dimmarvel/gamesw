#pragma once
#include "IUnit.hpp"

namespace sw::engine
{
	/**
	 * @class Heal
	 * @brief Represents a healing unit in the game.
	 *
	 * The Heal unit has the ability to restore health to other units. It is characterized
	 * by its unique ID, position on the map, health points (HP), and spiritual power (Spirit).
	 * This class implements the IUnit interface.
	 */
	class Heal final : public IUnit
	{
	public:
		Heal(size_t id, Position pos, int hp, int spirit);

		Position getPosition();
	};
}
