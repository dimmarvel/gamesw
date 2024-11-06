#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/System/PrintDebug.hpp>

#include <Engine/Renderer/IRenderer.hpp>
#include <Engine/Unit/UnitFactory.hpp>
#include <Engine/Position.hpp>
#include <Engine/Unit/Action/ActionFactory.hpp>

#include "GameObserver.hpp"
#include "Unit/IUnit.hpp"
#include "Settings.hpp"
#include "Tick.hpp"

namespace sw::engine
{
	GameObserver::GameObserver(Settings& s, std::unique_ptr<IRenderer> renderer) :
		settings(s),
		renderer(std::move(renderer))
	{}

	void GameObserver::addUnit(std::shared_ptr<IUnit> unit) 
	{
		units[unit->getId()] = unit;
		map.addUnit(unit);
		actionManager.registerUnit(unit);
	}

	bool GameObserver::removeUnit(unitId id)
	{
		auto unitIt = units.find(id);
		if(unitIt == units.end())
			return false;
		map.removeUnit(unitIt->second);
		return true;
	}

	UnitsMap GameObserver::getUnits()
	{
		return units;
	}

	void GameObserver::start() 
	{
		setup();
		while (true) {
			//TODO: log Tick
			renderer->renderMap(map);
			std::cout << "Tik: " << Tick::get().incrementTick() << std::endl;

			actionManager.processActions(map);
			if (checkGameEnd() || actionManager.isAllActionsCompleted()) {
				//TODO: log Game Over!
				break;
			}
			std::this_thread::sleep_for(std::chrono::seconds(1)); // Delay
		}
	}

	void GameObserver::setup()
	{
		auto self = shared_from_this();
		parser.add<io::CreateMap>([self](auto command) 
		{
			self->map = Map(self, command.width, command.height);

			printDebug(std::cout, command);
		})
		.add<io::SpawnSwordsman>([this](auto command)
		{ 
			addUnit(
				UnitFactory::createSwordsman(
				command.unitId,
				Position(command.x, command.y),
				command.hp,
				command.strength
			));
			printDebug(std::cout, command); 
			EventLog::get().log(io::UnitSpawned{command.unitId, "Swordsman", command.x, command.y});
		})
		.add<io::SpawnHunter>([this](auto command)
		{ 
			addUnit(
				UnitFactory::createHunter(
				command.unitId,
				Position(command.x, command.y),
				command.hp,
				command.agility,
				command.strength,
				command.range
			));
			printDebug(std::cout, command); 
			EventLog::get().log(io::UnitSpawned{command.unitId, "Hunter", command.x, command.y});

		})
		.add<io::March>([this](auto command)
		{
			actionManager.addAction(
				units[command.unitId],
				ActionFactory::createMove(Position(command.targetX, command.targetY))
			);
			printDebug(std::cout, command); 
		});
		parser.parse(settings.file);
	}

	bool GameObserver::checkGameEnd() {
		return units.size() <= 1; // Game is end if on map less then 1 unit
	}
}