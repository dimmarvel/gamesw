#pragma once
#include <cstdint>

namespace sw::engine
{
	class Position 
	{
	public:
		Position() = default;
		Position(uint32_t x, uint32_t y) : x(x), y(y) {}
		Position(const Position& other) = default;
		Position(Position&& other) noexcept = default;
		Position& operator=(const Position& other) = default;
		Position& operator=(Position&& other) noexcept = default;
		~Position() = default;

		uint32_t getX() const { return x; }
		uint32_t getY() const { return y; }

		void setX(uint32_t newX) { x = newX; }
		void setY(uint32_t newY) { y = newY; }

		void move(uint32_t deltaX, uint32_t deltaY)
		{
			x += deltaX;
			y += deltaY;
		}

	private:
		uint32_t x{};
		uint32_t y{};
	};
}