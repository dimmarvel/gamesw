#pragma once
#include <cstdint>

namespace sw::engine
{
	class Position 
	{
	public:
		Position() = default;
		Position(int x, int y) : x(x), y(y) {}
		Position(const Position& other) = default;
		Position(Position&& other) noexcept = default;
		Position& operator=(const Position& other) = default;
		Position& operator=(Position&& other) noexcept = default;
		~Position() = default;

		bool operator==(const Position& other) const noexcept
		{
			return x == other.x && y == other.y;
		}

		int getX() const { return x; }
		int getY() const { return y; }

		void setX(int newX) { x = newX; }
		void setY(int newY) { y = newY; }

		void move(int deltaX, int deltaY)
		{
			x += deltaX;
			y += deltaY;
		}

	private:
		int x{};
		int y{};
	};
}