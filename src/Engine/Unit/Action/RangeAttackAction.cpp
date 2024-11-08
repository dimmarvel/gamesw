#include "RangeAttackAction.hpp"

#include <Engine/Core/Map.hpp>
#include <Engine/Core/Utils.hpp>
#include <Engine/Unit/Components/HealthComponent.hpp>
#include <Engine/Unit/IUnit.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <IO/System/EventLog.hpp>

namespace sw::engine
{
	RangeAttackAction::RangeAttackAction(std::shared_ptr<IUnit> target, uint32_t dmg) :
			IAttackAction(target, dmg)
	{}

	bool RangeAttackAction::execute(std::shared_ptr<IUnit> attackerUnit, Map& map)
	{
		auto healthComponent = attackTarget->getComponent<HealthComponent>();
		healthComponent->takeDamage(damage);

		EventLog::get().log(
			io::UnitAttacked{
				attackerUnit->getId(),
				attackTarget->getId(),
				damage,
				static_cast<uint32_t>(healthComponent->getHealth()),
				utils::to_string(getType())});

		if (!healthComponent->isAlive())
		{
			healthComponent->processUnitDeath(attackTarget->getId(), map.getGameObserver());
		}

		return true;
	}
}
