#include "Heal.hpp"
#include "Components/MovementComponent.hpp"

#include <Engine/Unit/Components/HealthComponent.hpp>
#include <Engine/Unit/Components/HealingComponent.hpp>
#include <Engine/Unit/Components/RangeComponent.hpp>
#include <Engine/Unit/Components/RangeHealComponent.hpp>

namespace sw::engine
{
	Heal::Heal(size_t id, Position pos, int hp, int spirit)
	{
		setId(id);
		setType(UnitType::Heal);
		addComponent<HealthComponent>(hp);
		addComponent<HealingComponent>(spirit);
		addComponent<RangeHealComponent>(1, 2);
		addComponent<MovementComponent>(pos);
	}

	Position Heal::getPosition()
	{
		return getComponent<MovementComponent>()->getPosition();
	}
}
