#pragma once
#include <thread>
#include <memory>

#include <Engine/Unit/Action/ActoinManager.hpp>
#include <IO/System/CommandParser.hpp>

#include "Map.hpp"

namespace sw::engine
{
	class IUnit;
	class IRenderer;
	class Settings;

	using UnitsMap = std::unordered_map<unitId, std::shared_ptr<IUnit>>;

	class GameObserver : public std::enable_shared_from_this<GameObserver>
	{
	public:
		GameObserver(Settings& s, std::unique_ptr<IRenderer> renderer);
		
		void addUnit(std::shared_ptr<IUnit> unit);
		bool removeUnit(unitId id);
		UnitsMap getUnits();

		void start();
		void setup();

	private:
		bool checkGameEnd();

		Map map;
		Settings& settings;
		io::CommandParser parser;
		std::unique_ptr<IRenderer> renderer;
		ActionManager actionManager;
		UnitsMap units;
	};
}