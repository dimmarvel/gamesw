#include "HPComponent.hpp"
#include <Engine/GameObserver.hpp>
#include <IO/Events/UnitDied.hpp>
#include <IO/System/EventLog.hpp>

namespace sw::engine
{
	bool HPComponent::processUnitDeath(unitId id, std::shared_ptr<GameObserver> gObserver)
	{
		if(!gObserver->removeUnit(id))
			return false;
		EventLog::get().log(io::UnitDied{id});
		return true;
	}

	void HPComponent::takeDamage(int damage) 
	{
		if(health <= damage) [[unlikely]]
			health = 0;
		else [[likely]]
			health -= damage; 
	}

	bool HPComponent::isAlive() 
	{
		return health > 0;
	}
}
