#pragma once
#include <iostream>
#include "IUnit.hpp"
#include "Components/StrengthComponent.hpp"
#include "Components/AgilityComponent.hpp"
#include "Components/RangeComponent.hpp"
#include "Components/HPComponents.hpp"
#include <IO/Events/UnitAttacked.hpp>

namespace sw::engine
{
	class Hunter : public IUnit {
	public:
		Hunter(size_t id, Position pos, int health, int agility, int strenght, int range) // TODO: mabye do componentMap here
		{
			setId(id);
			addComponent<HPComponent>(health);
			addComponent<StrengthComponent>(strenght);
			addComponent<AgilityComponent>(agility);
			addComponent<RangeComponent>(agility);
			addComponent<MovementComponent>(pos);
		}

		void move(int dx, int dy) {
			//TODO: do logs
		}
		
		uint32_t rangeDamage()
		{
			return getComponent<AgilityComponent>()->agility;
		}

		uint32_t meleeDamage()
		{
			return getComponent<StrengthComponent>()->strength;
		}

		Position getPosition()
		{
			return getComponent<MovementComponent>()->getPosition();
		}

		void rangeAttack(IUnit& target) {
			auto rangeComp = getComponent<RangeComponent>();
			if (rangeComp) // TODO: throw if doesnt exist
			{
				auto targetHealth = target.getComponent<HPComponent>();
				if (targetHealth) 
				{
					targetHealth->takeDamage(meleeDamage());
					//TODO: do logs take damage mabue inside take damage
				}
			}
		}

		void meleeAttack(IUnit& target) {
			auto rangeComp = getComponent<RangeComponent>();
			if (rangeComp) // TODO: throw if doesnt exist
			{
				auto targetHealth = target.getComponent<HPComponent>();
				if (targetHealth) 
				{
					targetHealth->takeDamage(rangeDamage());
					//TODO: do logs take damage mabue inside take damage
				}
			}
		}
	};
}