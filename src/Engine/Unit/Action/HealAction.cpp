#include "HealAction.hpp"

#include <Engine/Core/Map.hpp>
#include <Engine/Core/Utils.hpp>
#include <Engine/Unit/Components/HealthComponent.hpp>
#include <Engine/Unit/Components/HealingComponent.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/Events/UnitHeal.hpp>

namespace sw::engine
{
	class Map;

	HealAction::HealAction(std::shared_ptr<IUnit> target, uint32_t sp) :
			healingTarget(target),
			spirit(sp)
	{}

	ActionType HealAction::getType() const
	{
		return ActionType::HealingAction;
	}

	bool HealAction::execute(std::shared_ptr<IUnit> healerUnit, Map& map)
	{
		auto healthTargetComponent = healingTarget->getComponent<HealthComponent>();
		auto healingComponent = healerUnit->getComponent<HealingComponent>();
		healthTargetComponent->takeHeal(spirit);

		EventLog::get().log(
			io::UnitHeal
			{
				healingTarget->getId(),
				healerUnit->getId(),
				spirit,
				static_cast<uint32_t>(healthTargetComponent->getHealth())
			});

		return true;
	}
}
