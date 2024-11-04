#pragma once
#include "IComponent.hpp"
#include "HPComponents.hpp"

class AgilityComponent : public IComponent {
public:
	int agility;
	
	AgilityComponent(int agil) : agility(agil) {}
	void update() override 
	{
		// TODO: logic
	}
};