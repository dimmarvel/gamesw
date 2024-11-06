#pragma once
#include "IComponent.hpp"

namespace sw::engine
{
	class HPComponent : public IComponent 
	{
	public:
		int health;

		explicit HPComponent(int hp) : health(hp) {}

		void takeDamage(int damage) 
		{
			if(health <= damage) [[unlikely]]
			{
				health = 0;
				return;
			}
			else [[likely]]
			{
				health -= damage; 
			}
		}
	};
}
