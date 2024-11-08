#include "HealthComponent.hpp"

#include <Engine/GameObserver.hpp>

#include <IO/Events/UnitDied.hpp>
#include <IO/System/EventLog.hpp>

namespace sw::engine
{
	HealthComponent::HealthComponent(int hp) : 
		health(hp)
	{}

	bool HealthComponent::processUnitDeath(unitId id, std::shared_ptr<GameObserver> gObserver)
	{
		if(!gObserver->removeUnit(id))
			return false;
		EventLog::get().log(io::UnitDied{id});
		return true;
	}

	void HealthComponent::takeDamage(int damage) 
	{
		if(health <= damage) [[unlikely]]
			health = 0;
		else [[likely]]
			health -= damage; 
	}

	bool HealthComponent::isAlive() 
	{
		return health > 0;
	}
}
