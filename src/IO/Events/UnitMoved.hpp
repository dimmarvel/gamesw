#pragma once

#include <cstdint>
#include <string>
#include <Engine/Unit/IUnit.hpp>

namespace sw::io
{
	struct UnitMoved
	{
		constexpr static const char* Name = "UNIT_MOVED";

		engine::IUnit::unitId unitId{};
		uint32_t x{};
		uint32_t y{};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("x", x);
			visitor.visit("y", y);
		}
	};
}
