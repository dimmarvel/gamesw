#pragma once
#include <cstdint>

namespace sw::engine
{
	/**
	 * @class Position
	 * @brief Represents a position in a 2D space, typically used for placing units on a map.
	 * 
	 * The `Position` class is used to encapsulate the coordinates of a unit or object within 
	 * a 2D grid. It provides utility methods for accessing and modifying these coordinates,
	 * as well as for comparing positions and moving them in relation to other positions.
	 */
	class Position final
	{
	private:
		int x{};
		int y{};

	public:
		Position() = default;

		Position(int x, int y) :
				x(x),
				y(y)
		{}

		Position(const Position& other) = default;
		Position(Position&& other) noexcept = default;

		Position& operator=(const Position& other) = default;
		Position& operator=(Position&& other) noexcept = default;

		~Position() = default;

		bool operator==(const Position& other) const noexcept
		{
			return x == other.x && y == other.y;
		}

		inline int getX() const noexcept
		{
			return x;
		}

		inline int getY() const noexcept
		{
			return y;
		}

		void setX(int newX)
		{
			x = newX;
		}

		void setY(int newY)
		{
			y = newY;
		}

		void move(int deltaX, int deltaY)
		{
			x += deltaX;
			y += deltaY;
		}
	};
}
