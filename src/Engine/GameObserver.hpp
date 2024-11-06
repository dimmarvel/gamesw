#pragma once
#include <thread>
#include <memory>
#include <IO/System/CommandParser.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/Commands/March.hpp>
#include <IO/System/EventLog.hpp>
#include "Unit/IUnit.hpp"
#include "Map.hpp"
#include <Engine/Renderer/IRenderer.hpp>
#include "Settings.hpp"
#include <Engine/Unit/UnitFactory.hpp>
#include <Engine/Position.hpp>
#include <Engine/Unit/Action/ActoinManager.hpp>
#include <Engine/Unit/Action/ActionFactory.hpp>
#include "Tick.hpp"
#include <IO/System/EventLog.hpp>

namespace sw::engine
{
	class GameObserver {
	public:
		GameObserver(Settings& s, std::unique_ptr<IRenderer> renderer) : 
			map(s.map_width, s.map_width),
			settings(s),
			renderer(std::move(renderer))
		{
			setup();
		}

		void addUnit(std::shared_ptr<IUnit> unit) 
		{
			units[unit->getId()] = unit;
			map.addUnit(unit);
			actionManager.registerUnit(unit);
		}

		bool removeUnit(IUnit::unitId id)
		{
			auto unitIt = units.find(id);
			if(unitIt == units.end())
				return false;
			map.removeUnit(unitIt->second);
			return true;
		}

		std::unordered_map<size_t, std::shared_ptr<IUnit>> getUnits()
		{
			return units;
		}

		void start() 
		{
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

		void setup()
		{
			parser.add<io::CreateMap>([this](auto command) 
			{
				map = engine::Map(command.width, command.height); 

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

	private:
		bool checkGameEnd() {
			return units.size() <= 1; // Game is end if on map less then 1 unit
		}

		Map map;
		Settings& settings;
		io::CommandParser parser;
		std::unique_ptr<IRenderer> renderer;
		ActionManager actionManager;
		std::unordered_map<IUnit::unitId, std::shared_ptr<IUnit>> units;
	};
}