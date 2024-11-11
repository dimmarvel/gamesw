#include "Map.hpp"

#include "GameObserver.hpp"
#include "Position.hpp"
#include "Utils.hpp"

#include <Engine/Unit/IUnit.hpp>
#include <IO/System/PrintDebug.hpp>
#include <cmath>
#include <random>

namespace sw::engine
{
	Cell::Cell(int x, int y) :
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
		if (this != &other)
		{
			unit = other.unit;
			pos = other.pos;
		}
		return *this;
	}

	Map::Map(std::shared_ptr<GameObserver> gObserver, int height, int width) :
			gameObserver(gObserver)
	{
		cells.resize(height, std::vector<Cell>(width));
		feelMap(height, width);
	}

	Map::Map(const Map& other) :
			cells(other.cells),
			gameObserver(other.gameObserver)
	{}

	Map& Map::operator=(const Map& other)
	{
		if (this != &other)
		{
			cells = other.cells;
			gameObserver = other.gameObserver;
		}
		return *this;
	}

	Cell Map::getCellContent(int x, int y) const
	{
		return cells[x][y];
	}

	Cell Map::getCellContent(const Position& pos) const
	{
		return cells[pos.getX()][pos.getY()];
	}

	void Map::addUnit(std::shared_ptr<IUnit> unit)
	{
		auto pos = unit->getPosition();
		cells[pos.getX()][pos.getY()].placeUnit(unit);
	}

	void Map::moveUnit(std::shared_ptr<IUnit> unit, Position newPos)
	{
		auto otherUnitInCell = getCellContent(newPos).getUnit();

		if (otherUnitInCell)
		{
			// TODO: should move to C++20 and use std::format :)
			throw std::runtime_error(
				std::string("Attempt to move unit with ID=") + std::to_string(unit->getId()) + " at position ("
				+ std::to_string(unit->getPosition().getX()) + "," +  std::to_string(unit->getPosition().getY()) + ")" + 
				", to position(" + std::to_string(newPos.getX()) + "," + std::to_string(newPos.getX()) + ") " +
				", but cell is occupied by unit with ID=" + std::to_string(otherUnitInCell->getId()));
		}

		auto cell = getCellContent(unit->getPosition());

		setCellContent(newPos, Cell(newPos, unit));
		removeUnit(unit);
	}

	std::optional<unitPtrVec> Map::getAdjacentUnits(const Position& pos)
	{
		unitPtrVec adjacentUnits;
		for (int dx = -1; dx <= 1; ++dx)
		{
			for (int dy = -1; dy <= 1; ++dy)
			{
				// Skip current position
				if (dx == 0 && dy == 0)
				{
					continue;
				}
				Position adjacent(pos.getX() + dx, pos.getY() + dy);
				if (!isWithinBounds(adjacent))
				{
					continue;
				}
				auto adjUnit = getUnitAt(adjacent);
				if (adjUnit != nullptr)
				{
					adjacentUnits.push_back(adjUnit);
				}
			}
		}

		if (adjacentUnits.size() == 0)
		{
			return {};
		}
		return adjacentUnits;
	}

	std::shared_ptr<IUnit> Map::getRandomAdjacentUnit(const Position& pos)
	{
		auto unitsOpt = getAdjacentUnits(pos);
		if (!unitsOpt.has_value())
		{
			return nullptr;
		}

		if (!unitsOpt.value().empty())
		{
			return unitsOpt.value()[rand() % unitsOpt.value().size()];
		}

		return nullptr;
	}

	bool Map::isWithinBounds(const Position& pos)
	{
		return pos.getX() >= 0 && pos.getX() < getSizeX() && pos.getY() >= 0 && pos.getY() < getSizeY();
	}

	std::shared_ptr<IUnit> Map::findRandomUnitInRange(
		std::shared_ptr<IUnit> unit, Map& map, uint32_t minRange, uint32_t maxRange)
	{
		std::vector<std::shared_ptr<IUnit>> validTargets;

		for (const auto& potentialTarget : gameObserver->getUnits())
		{
			auto& potentialTargetUnit = potentialTarget.second;
			if (potentialTargetUnit != unit
				&& isWithinRange(unit->getPosition(), potentialTargetUnit->getPosition(), minRange, maxRange))
			{
				validTargets.push_back(potentialTargetUnit);
			}
		}

		if (validTargets.empty())
		{
			return nullptr;
		}

		size_t randomIndex = utils::getRandom(0, validTargets.size() - 1);
		return validTargets[randomIndex];
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
		if (!cellUnit)
		{
			return nullptr;
		}
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

	void Map::feelMap(int height, int width)
	{
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				cells[y][x] = Cell(x, y);
			}
		}
	}
}
