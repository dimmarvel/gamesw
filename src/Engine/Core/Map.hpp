#pragma once
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <memory>
#include <optional>

#include "Position.hpp"
#include <Engine/Unit/IUnit.hpp>

namespace sw::engine
{
	class IUnit;
	class GameObserver;

	class Cell final
	{
	public:
		Cell() = default;
		Cell(int x, int y);
		Cell(Position pos, std::shared_ptr<IUnit> u);
		Cell(const Cell& other);
		Cell& operator=(const Cell& other);

		/**
		 * @brief Checks if the cell is empty (i.e., has no unit).
		 * @return True if the cell is empty, false otherwise.
		 */
		bool isEmpty() const { return unit == nullptr; }
		
		/**
		 * @brief Places a unit in the cell.
		 * @param newUnit A shared pointer to the unit to place in the cell.
		 */
		void placeUnit(std::shared_ptr<IUnit> newUnit) { unit = newUnit; }

		/**
		 * @brief Removes the unit from the cell, making it empty.
		 */
		void removeUnit() { unit.reset(); }

		/**
		 * @brief Retrieves the unit currently in the cell.
		 * @return A shared pointer to the unit in the cell, or nullptr if the cell is empty.
		 */
		inline std::shared_ptr<IUnit> getUnit() const noexcept { return unit; }
		
		inline int getX() const noexcept { return pos.getX(); }
		inline int getY() const noexcept { return pos.getY(); }

		inline Position getPosition() const noexcept { return pos; }
		inline void setPosition(Position pos) noexcept { pos = pos; }

	private:
		std::shared_ptr<IUnit> unit;
		Position pos;
	};

	class Map final
	{
	private:
		std::vector<std::vector<Cell>> cells;
		std::shared_ptr<GameObserver> gameObserver;

	public:
		Map() = default;
		Map(std::shared_ptr<GameObserver> gObserver, int height, int width);
		Map(const Map& other);
		Map& operator=(const Map& other);
		~Map() = default;

		std::shared_ptr<GameObserver> getGameObserver() { return gameObserver; }

		inline int getSizeX() const noexcept { return cells.size(); }
		inline int getSizeY() const noexcept { return cells.at(0).size(); }

		/**
		 * @brief Retrieves the content of a cell at specified coordinates.
		 * @param x The x-coordinate.
		 * @param y The y-coordinate.
		 * @return The content of the cell at (x, y).
		 */
		Cell getCellContent(int x, int y) const;

		/**
		 * @brief Retrieves the content of a cell at a specified position.
		 * @param pos The Position object.
		 * @return The content of the cell at the specified position.
		 */
		Cell getCellContent(const Position& pos) const;

		/**
		 * @brief Sets the content of a cell at a specified position.
		 * @param pos The position to update.
		 * @param cell The cell content to set.
		 */
		void setCellContent(Position pos, Cell cell);

		/**
		 * @brief Adds a unit to the map.
		 * @param unit The unit to add.
		 */
		void addUnit(std::shared_ptr<IUnit> unit);

		/**
		 * @brief Moves a unit to a new position on the map.
		 * @param unit The unit to move.
		 * @param newPos The target position.
		 */
		void moveUnit(std::shared_ptr<IUnit> unit, Position newPos);

		/**
		 * @brief Removes a unit from the map.
		 * @param unit The unit to remove.
		 * @return True if the unit was successfully removed, false otherwise.
		 */
		bool removeUnit(std::shared_ptr<IUnit> unit);

		/**
		 * @brief Retrieves units in adjacent cells around a given position.
		 * @param pos The central position to search around.
		 * @return An optional vector of pointers to adjacent units.
		 */
		std::optional<unitPtrVec> getAdjacentUnits(const Position& pos);

		/**
		 * @brief Retrieves a random adjacent unit around a given position.
		 * @param pos The central position to search around.
		 * @return A shared pointer to a randomly selected adjacent unit.
		 */
		std::shared_ptr<IUnit> getRandomAdjacentUnit(const Position& pos);

		/**
		 * @brief Retrieves a unit located at a specified position.
		 * @param pos The position to check.
		 * @return A shared pointer to the unit at the specified position.
		 */
		std::shared_ptr<IUnit> getUnitAt(const Position& pos);

		/**
		 * @brief Finds a unit within a specified range from another unit.
		 * @param unit The unit from which to measure the range.
		 * @param map The map where the unit is located.
		 * @param minRange The minimum search range.
		 * @param maxRange The maximum search range.
		 * @return A shared pointer to a unit found within the specified range.
		 */
		std::shared_ptr<IUnit> findUnitInRange(std::shared_ptr<IUnit> unit, Map& map, uint32_t minRange, uint32_t maxRange);
		
		/**
		 * @brief Checks if a position is within the bounds of the map.
		 * @param pos The position to check.
		 * @return True if within bounds, false otherwise.
		 */
		bool isWithinBounds(const Position& pos);

		/**
		 * @brief Checks if a position is within a specified range from another position.
		 * @param from The starting position.
		 * @param to The position to check against.
		 * @param minRange The minimum allowed range.
		 * @param maxRange The maximum allowed range.
		 * @return True if within the specified range, false otherwise.
		 */
		bool isWithinRange(const Position& from, const Position& to, int minRange, int maxRange);

	private:
		/**
		 * @brief Fills the map with the specified dimensions.
		 * @param height The number of rows (height) of the map.
		 * @param width The number of columns (width) of the map.
		 */
		void feelMap(int height, int width);
	};
}