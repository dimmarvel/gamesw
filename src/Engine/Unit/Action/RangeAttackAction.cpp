#include "RangeAttackAction.hpp"

#include <Engine/Unit/Components/HPComponent.hpp>
#include <Engine/Unit/IUnit.hpp>
#include <Engine/Map.hpp>

#include <IO/System/EventLog.hpp>
#include <IO/Events/UnitAttacked.hpp>

namespace sw::engine
{
	RangeAttackAction::RangeAttackAction(std::shared_ptr<IUnit> target, uint32_t dmg) :
		IAttackAction(target, dmg)
	{}

	bool RangeAttackAction::execute(std::shared_ptr<IUnit> attackerUnit, Map& map)
	{
		auto hpComponent = attackTarget->getComponent<HPComponent>();
		hpComponent->takeDamage(damage);

		EventLog::get().log(io::UnitAttacked
		{
			attackerUnit->getId(),
			attackTarget->getId(),
			damage,
			hpComponent->health,
			to_string(getType())
		});
		
		if(hpComponent->isAlive())
			hpComponent->processUnitDeath(attackTarget->getId(), map.getGameObserver());

		return true;
	}
}