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

namespace sw::engine
{
	class GameObserver {
	public:
		GameObserver(int width, int height, std::ifstream& file, EventLog& log) : 
			map(width, height),
			tick(0),
			eventLog(log)
		{
			parser.add<io::CreateMap>([this](auto command) 
			{
				map = engine::Map(command.width, command.height); 
				printDebug(std::cout, command); 
			})
			.add<io::SpawnSwordsman>([](auto command)
			{ 
				printDebug(std::cout, command); 
			})
			.add<io::SpawnHunter>([](auto command)
			{ 
				printDebug(std::cout, command); 
			})
			.add<io::March>([](auto command)
			{ 
				printDebug(std::cout, command); 
			});
			parser.parse(file);
		}

		void addUnit(std::shared_ptr<IUnit> unit, int x, int y) {
			if (!map.addUnit(unit, x, y)) {
				//TODO: log failed to place unit
			}
		}

		void start() {
			while (true) {
				//TODO: log Tick
				map.update(); // Update map state
				map.display(); // Show Map
				tick++;
				if (checkGameEnd()) {
					//TODO: log Game Over!
					break;
				}
				std::this_thread::sleep_for(std::chrono::seconds(1)); // Delay
			}
		}

	private:
		bool checkGameEnd() {
			return map.getUnits().size() <= 1; // Game is end if on map less then 1 unit
		}

		Map map;
		int tick;
		io::CommandParser parser;
		EventLog& eventLog; // Ссылка на логгер
	};
}