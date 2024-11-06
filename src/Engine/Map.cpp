#include "Map.hpp"
#include <IO/System/PrintDebug.hpp>
#include "Unit/IUnit.hpp"
#include "Position.hpp"
#include "GameObserver.hpp"
#include <cmath>

namespace sw::engine
{
	Cell::Cell(uint32_t x, uint32_t y) : 
		unit(nullptr),
		pos(x, y)
	{}

	Cell::Cell(Position pos, std::shared_ptr<IUnit> u) : 
		unit(u),
		pos(pos)
	{}

	Cell::Cell(const Cell& other) :
		unit(other.unit), 
		pos(other.pos) 
	{}

	Cell& Cell::operator=(const Cell& other) 
	{
		if (this != &other) {
			unit = other.unit;
			pos = other.pos;
		}
		return *this;
	}

	Map::Map(std::shared_ptr<GameObserver> gObserver, uint32_t height, uint32_t width)
	{
		cells.resize(height, std::vector<Cell>(width));
		feelMap(height, width);
	}

	Map::Map(const Map& other)
		: cells(other.cells),
		gameObserver(other.gameObserver)
	{}

	Map& Map::operator=(const Map& other) {
		if (this != &other) {
			cells = other.cells;
			gameObserver = other.gameObserver;
		}
		return *this;
	}

	Cell Map::getCellContent(uint32_t x, uint32_t y) const 
	{
		//TODO: do checks cout of range
		return cells[y][x]; 
	}

	Cell Map::getCellContent(const Position& pos) const 
	{
		//TODO: do checks cout of range
		return cells[pos.getX()][pos.getY()]; 
	}

	void Map::addUnit(std::shared_ptr<IUnit> unit)
	{
		auto pos = unit->getPosition();
		cells[pos.getX()][pos.getY()].placeUnit(unit);
	}

	void Map::moveUnit(std::shared_ptr<IUnit> unit, Position newPos)
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

	std::optional<unitPtrVec> Map::getAdjacentUnits(const Position& pos)
	{
		unitPtrVec adjacentUnits;
		for (int dx = -1; dx <= 1; ++dx) {
			for (int dy = -1; dy <= 1; ++dy) {
				if (dx == 0 && dy == 0) continue; // Skip current position
					Position adjacent(pos.getX() + dx, pos.getY() + dy);
					auto adjUnit = getUnitAt(adjacent);
					if (isWithinBounds(adjacent) && (adjUnit != nullptr)) {
						adjacentUnits.push_back(adjUnit);
				}
			}
		}

		if(adjacentUnits.size() == 0)
			return {};
		return adjacentUnits;
	}

	std::shared_ptr<IUnit> Map::getRandomAdjacentUnit(const Position& pos)
	{
		auto unitsOpt = getAdjacentUnits(pos);
		if(!unitsOpt.has_value())
			return nullptr;
		
		if (!unitsOpt.value().empty()) 
			return unitsOpt.value()[rand() % unitsOpt.value().size()];

		return nullptr;
	}

	bool Map::isWithinBounds(const Position& pos)
	{
		return pos.getX() >= 0 && pos.getX() < getSizeX() &&
			pos.getY() >= 0 && pos.getY() < getSizeY();
	}

	std::shared_ptr<IUnit> Map::findUnitInRange(std::shared_ptr<IUnit> unit, Map& map, uint32_t minRange, uint32_t maxRange) 
	{
		for (const auto& potentialTarget : gameObserver->getUnits()) {
			auto& potentialTargetUnit = potentialTarget.second;
			if (potentialTargetUnit != unit && isWithinRange(unit->getPosition(), potentialTargetUnit->getPosition(), minRange, maxRange)) {
				return potentialTargetUnit;
			}
		}
		return nullptr;
	}
	
	bool Map::isWithinRange(const Position& from, const Position& to, int minRange, int maxRange)
	{
		int deltaX = std::abs(static_cast<int>(from.getX()) - static_cast<int>(to.getX()));
		int deltaY = std::abs(static_cast<int>(from.getY()) - static_cast<int>(to.getY()));
		
		// Use the Euclidean distance, for simplicity we can replace it with Manhattan distance or another one
		double distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

		// Checking whether the target is within the acceptable range
		return distance >= minRange && distance <= maxRange;
	}

	std::shared_ptr<IUnit> Map::getUnitAt(const Position& pos) 
	{
		auto cellContent = getCellContent(pos);
		auto cellUnit = cellContent.getUnit();
		if(!cellUnit)
			return nullptr;
		return cellUnit;
	}

	bool Map::removeUnit(std::shared_ptr<IUnit> unit)
	{
		auto position = unit->getPosition();
		cells[position.getX()][position.getY()].removeUnit();
		return true;
	}

	void Map::setCellContent(Position pos, Cell cell) 
	{
		cells[pos.getX()][pos.getY()] = cell;
	}

	void Map::feelMap(uint32_t height, uint32_t width)
	{
		for (uint32_t y = 0; y < height; ++y)
			for (uint32_t x = 0; x < width; ++x)
				cells[y][x] = Cell(x, y);
	}
}