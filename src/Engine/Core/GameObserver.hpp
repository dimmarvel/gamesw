#pragma once
#include "Map.hpp"

#include <Engine/Unit/Action/ActoinManager.hpp>
#include <IO/System/CommandParser.hpp>
#include <memory>
#include <thread>

namespace sw::engine
{
	class IUnit;
	class IRenderer;
	class Settings;

	using UnitsMap = std::unordered_map<unitId, std::shared_ptr<IUnit>>;

	/**
	 * @class GameObserver
	 * @brief Manages the game state, including units, map, and actions.
	 * 
	 * The `GameObserver` class observes the game state and coordinates the flow of the game.
	 * It manages units, processes actions, and determines when the game ends. The class 
	 * also handles rendering the map and setting up the game environment.
	 * 
	 * @see IRenderer, ActionManager, Map, UnitsMap
	 */

	class GameObserver final : public std::enable_shared_from_this<GameObserver>
	{
		Map map;
		Settings& settings;
		io::CommandParser parser;
		std::unique_ptr<IRenderer> renderer;
		ActionManager actionManager;
		UnitsMap units;

	public:
		/**
		 * @brief Constructor for creating a GameObserver instance.
		 * Initializes the game observer with settings and a renderer.
		 * @param s The game settings to configure the observer.
		 * @param renderer The renderer used to display the game map.
		 */
		GameObserver(Settings& s, std::unique_ptr<IRenderer> renderer);

		/**
		 * @brief Adds a unit to the game.
		 * Registers the unit with the `ActionManager`, adds it to the map, and stores it in the unit list.
		 * @param unit The unit to add to the game.
		 */
		void addUnit(std::shared_ptr<IUnit> unit);

		/**
		 * @brief Removes a unit from the game.
		 * Unregisters the unit from the `ActionManager`, removes it from the map, and deletes it from the unit list.
		 * @param id The unique ID of the unit to remove.
		 * @return `true` if the unit was successfully removed, `false` otherwise.
		 */
		bool removeUnit(unitId id);

		/**
		 * @brief Retrieves all units in the game.
		 * @return A map of all units in the game, keyed by unit ID.
		 */
		UnitsMap getUnits();

		/**
		 * @brief Starts the game loop.
		 * Begins the game, processing actions and rendering the map until the game ends or all actions are completed.
		 * The loop runs until a game-over condition is met.
		 */
		void start();

		/**
		 * @brief Sets up the game by parsing commands and adding units.
		 * 
		 * Configures the game state by processing the setup commands such as creating the map and spawning units.
		 * This function is typically called at the start of the game.
		 */
		void setup();

	private:
		/**
		 * @brief Checks if the game has ended.
		 * 
		 * The game is considered over if there is one or fewer units remaining.
		 * 
		 * @return `true` if the game has ended, `false` otherwise.
		 */
		bool checkGameEnd();
	};
}
