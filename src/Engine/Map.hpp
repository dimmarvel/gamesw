#pragma once
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <memory>
#include "IO/System/PrintDebug.hpp"
#include "Unit/IUnit.hpp"
#include "Position.hpp"

namespace sw::engine
{
	class Cell 
	{
	public:
		Cell() = default;
		Cell(uint32_t x, uint32_t y) : 
			unit(nullptr),
			pos(x, y)
		{}
		Cell(Position pos, std::shared_ptr<IUnit> u) : 
			unit(u),
			pos(pos)
		{}

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

	public:
		Map() = default;
		Map(uint32_t height, uint32_t width)
		{
			cells.resize(height, std::vector<Cell>(width));
			feelMap(height, width);
		}

		uint32_t getSizeX() const { return cells.size(); }
		uint32_t getSizeY() const { return cells.at(0).size(); } // TODO: error check

		Cell getCellContent(uint32_t x, uint32_t y) const 
		{
			//TODO: do checks cout of range
			return cells[y][x]; 
		}

		Cell getCellContent(Position pos) const 
		{
			//TODO: do checks cout of range
			return cells[pos.getX()][pos.getY()]; 
		}

		void addUnit(std::shared_ptr<IUnit> unit)
		{
			auto pos = unit->getPosition();
			cells[pos.getX()][pos.getY()].placeUnit(unit);
		}

		void moveUnit(std::shared_ptr<IUnit> unit, Position newPos)
		{
			auto cellUnit = getCellContent(unit->getPosition()).getUnit();
			if(!cellUnit)
				throw std::runtime_error(std::string("Attempting to move a unit in a cell in which it does not exist"));
			if(cellUnit->getId() != unit->getId())
				throw std::runtime_error("Attempt to move another unit into position");
			
			auto cell = getCellContent(unit->getPosition());
			
			setCellContent(newPos, Cell(newPos, unit));
			removeUnit(unit);
		}

		bool removeUnit(std::shared_ptr<IUnit> unit)
		{
			auto position = unit->getPosition();
			cells[position.getX()][position.getY()].removeUnit();
			return true;
		}

		void setCellContent(Position pos, Cell cell) 
		{
			cells[pos.getX()][pos.getY()] = cell;
		}

	private:
		
		void feelMap(uint32_t height, uint32_t width)
		{
			for (uint32_t y = 0; y < height; ++y)
				for (uint32_t x = 0; x < width; ++x)
					cells[y][x] = Cell(x, y);
		}

	};
}