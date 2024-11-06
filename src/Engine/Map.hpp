#pragma once
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <memory>
#include <optional>

#include "Position.hpp"
#include "Unit/IUnit.hpp"

namespace sw::engine
{
	class IUnit;
	class GameObserver;

	class Cell 
	{
	public:
		Cell() = default;
		Cell(uint32_t x, uint32_t y);
		Cell(Position pos, std::shared_ptr<IUnit> u);
		Cell(const Cell& other);
		Cell& operator=(const Cell& other);

		bool isEmpty() const 
		{ 
			return unit == nullptr; 
		}

		void placeUnit(std::shared_ptr<IUnit> newUnit) 
		{
			unit = newUnit;
		}

		void removeUnit()
		{
			unit.reset();
		}

		std::shared_ptr<IUnit> getUnit() const 
		{
			return unit;
		}

		uint32_t getX() const 
		{
			return pos.getX();
		}

		uint32_t getY() const 
		{
			return pos.getY();
		}

		Position getPosition() const 
		{
			return pos;
		}
		
		void setPosition(Position pos) const 
		{
			pos = pos;
		}

	private:
		std::shared_ptr<IUnit> unit;
		Position pos;
	};

	class Map 
	{
	private:
		std::vector<std::vector<Cell>> cells;
		std::shared_ptr<GameObserver> gameObserver;

	public:
		Map() = default;
		Map(std::shared_ptr<GameObserver> gObserver, uint32_t height, uint32_t width);
		Map(const Map& other);
		Map& operator=(const Map& other);
		~Map() = default;

		uint32_t getSizeX() const { return cells.size(); }
		uint32_t getSizeY() const { return cells.at(0).size(); } // TODO: error check

		Cell getCellContent(uint32_t x, uint32_t y) const;
		Cell getCellContent(const Position& pos) const;
		void setCellContent(Position pos, Cell cell);

		void addUnit(std::shared_ptr<IUnit> unit);
		void moveUnit(std::shared_ptr<IUnit> unit, Position newPos);
		bool removeUnit(std::shared_ptr<IUnit> unit);
		std::optional<unitPtrVec> getAdjacentUnits(const Position& pos);
		std::shared_ptr<IUnit> getRandomAdjacentUnit(const Position& pos);
		std::shared_ptr<IUnit> getUnitAt(const Position& pos);

		std::shared_ptr<IUnit> findUnitInRange(std::shared_ptr<IUnit> unit, Map& map, uint32_t minRange, uint32_t maxRange);
		
		// The coordinates are inside the map to avoid going out of bounds
		bool isWithinBounds(const Position& pos);
		bool isWithinRange(const Position& from, const Position& to, int minRange, int maxRange);


	private:
		void feelMap(uint32_t height, uint32_t width);
	};
}