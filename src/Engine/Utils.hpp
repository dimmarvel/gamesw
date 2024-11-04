#pragma once
#include <stdexcept>
#include <cassert>

namespace sw::engine::utils
{

//TODO: move to some other place

enum class UnitType
{
	Swordsman,
	Hunter,
	Archer,
	None, // Empty cell
};

inline char unitTypeToChar(UnitType type) {
	switch (type) {
		case UnitType::Swordsman: return 'S';
		case UnitType::Hunter: return 'H';
		case UnitType::Archer: return 'A';
		case UnitType::None: return '.';
		default:	
		{
			assert(false && "Unknown UnitType encountered in unitTypeToChar");
		}
	}
}

}