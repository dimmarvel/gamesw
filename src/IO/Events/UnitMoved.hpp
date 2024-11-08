#pragma once

#include <Engine/Unit/IUnit.hpp>
#include <cstdint>
#include <string>

namespace sw::io
{
	struct UnitMoved
	{
		constexpr static const char* Name = "UNIT_MOVED";

		engine::unitId unitId{};
		int x{};
		int y{};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("x", x);
			visitor.visit("y", y);
		}
	};
}
