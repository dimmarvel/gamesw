#pragma once
#include <Engine/Unit/IUnit.hpp>

namespace sw::engine
{
	class Map;
	
	class IAction 
	{
	public:
		virtual void execute(std::shared_ptr<IUnit> unit, Map& map) = 0;
		virtual ~IAction() = default;
	};
}
