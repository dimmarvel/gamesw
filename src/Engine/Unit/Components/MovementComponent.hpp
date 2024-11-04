#pragma once
#include "IComponent.hpp"

class MovementComponent : public IComponent 
{
private:
	int x, y;

public:
	MovementComponent(int startX, int startY, int spd) : 
			x(startX), 
			y(startY)
	{}

	void move(int targetX, int targetY) 
	{
		// TODO: logic
	}

	void update() override 
	{
		// TODO: logic
	}
};
