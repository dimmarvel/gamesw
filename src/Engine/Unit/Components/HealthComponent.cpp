#include "HealthComponent.hpp"

#include <Engine/Core/GameObserver.hpp>
#include <IO/Events/UnitDied.hpp>
#include <IO/System/EventLog.hpp>

namespace sw::engine
{
	HealthComponent::HealthComponent(int hp) :
			health(hp)
	{}

	bool HealthComponent::processUnitDeath(unitId id, std::shared_ptr<GameObserver> gObserver)
	{
		if (!gObserver->removeUnit(id))
		{
			return false;
		}
		EventLog::get().log(io::UnitDied{static_cast<uint32_t>(health)});
		return true;
	}

	void HealthComponent::takeDamage(int damage)
	{
		if (health <= damage) [[unlikely]]
		{
			health = 0;
		}
		else [[likely]]
		{
			health -= damage;
		}
	}

	void HealthComponent::takeHeal(int spirit)
	{
		health += spirit;
	}

	bool HealthComponent::isAlive()
	{
		return health > 0;
	}
}
