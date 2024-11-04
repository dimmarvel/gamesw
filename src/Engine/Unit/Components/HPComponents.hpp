#pragma once
#include "IComponent.hpp"

class HPComponent : public IComponent 
{
	int health;
public:
	HPComponent(int hp) : health(hp) {}
	void takeDamage(int damage) { health -= damage; }
	void update() override 
	{
		// TODO: logic
	}
};
