#pragma once
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <memory>
#include "IO/System/PrintDebug.hpp"
#include "Unit/IUnit.hpp"

namespace sw::engine
{
	class Map 
	{
	private:
		uint32_t width;
		uint32_t height;
		std::vector<std::vector<char>> cells;

	public:
		Map() = default;
		Map(uint32_t width, uint32_t height) : 
				width(width), 
				height(height), 
				cells(height, std::vector<char>(width, '.')) 
		{}

		uint32_t getWidth() const { return width; }
		uint32_t getHeight() const { return height; }

		char getCellContent(uint32_t x, uint32_t y) const 
		{
			//TODO: do checks cout of range
			return cells[y][x]; 
		}

		void update()
		{
			//TODO: update map state
		}

		void display()
		{
			//TODO: display map logic
		}

		bool addUnit(std::shared_ptr<IUnit> unit, uint32_t x, uint32_t y)
		{
			//TODO: addUnit map logic
			return true;
		}
		
		std::unordered_map<size_t, std::shared_ptr<IUnit>> getUnits()
		{
			//TODO: add units
			return {};
		}

		void setCellContent(uint32_t x, uint32_t y, char content) 
		{
			cells[y][x] = content;
		}
	};
}