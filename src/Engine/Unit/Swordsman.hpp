#pragma once
#include <iostream>
#include "IUnit.hpp"
#include "Components/StrengthComponent.hpp"
#include "Components/HPComponent.hpp"
#include "Components/MovementComponent.hpp"
#include "Components/MeleeAttackComponent.hpp"
#include <IO/Events/UnitAttacked.hpp>
#include <IO/System/EventLog.hpp>

namespace sw::engine
{
	class Swordsman : public IUnit {
	public:
		Swordsman(size_t id, Position pos, int hp, int strenght) 
		{
			setId(id);
			addComponent<HPComponent>(hp);
			addComponent<StrengthComponent>(strenght);
			addComponent<MovementComponent>(pos);
			addComponent<MeleeAttackComponent>();
		}

		void move(int dx, int dy) {
			//TODO: do logs
		}

		void attack(IUnit& target) {
			auto strenghtComp = getComponent<StrengthComponent>();
			if (strenghtComp)
			{
				auto targetHealth = target.getComponent<HPComponent>();
				if (targetHealth) {
					targetHealth->takeDamage(strenghtComp->strength);
					//TODO: do logs take damage mabue inside take damage
				}
			}
		}

		Position getPosition()
		{
			return getComponent<MovementComponent>()->getPosition();
		}
	};
}