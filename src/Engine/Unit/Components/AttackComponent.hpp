#pragma once
#include "IComponent.hpp"
#include "HPComponents.hpp"

class AttackComponent : public IComponent 
{
private:
	int power;

public:
	AttackComponent(int p) : power(p) {}

	void attack(HPComponent& target) {
		target.takeDamage(power);
	}

	void update() override 
	{
		// TODO: logic
	}
};
