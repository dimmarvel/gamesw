#pragma once
#include <memory>
#include "Raven.hpp"

class UnitFactory 
{
public:
	static std::unique_ptr<IUnit> createRaven(size_t id, int x, int y, int health, int strength) {
		return std::make_unique<Raven>(id, health, strength);
	}

};