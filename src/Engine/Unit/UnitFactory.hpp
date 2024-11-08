#pragma once
#include <memory>
#include "Swordsman.hpp"
#include "Hunter.hpp"
#include <Engine/Core/Position.hpp>

namespace sw::engine
{
	class UnitFactory final
	{
	public:
		static std::shared_ptr<IUnit> createSwordsman(size_t id, Position pos, int health, int strength)
		{
			return std::make_shared<Swordsman>(id, pos, health, strength);
		}

		static std::shared_ptr<IUnit> createHunter(size_t id, Position pos, int health, int agility, int strength, int range)
		{
			return std::make_shared<Hunter>(id, pos, health, agility, strength, range);
		}
	};
}