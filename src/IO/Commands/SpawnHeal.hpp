#pragma once

#include <cstdint>
#include <iosfwd>

namespace sw::io
{
	struct SpawnHeal
	{
		constexpr static const char* Name = "SPAWN_HEAL";

		uint32_t unitId{};
		int x{};
		int y{};
		uint32_t hp{};
		uint32_t spirit{};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("x", x);
			visitor.visit("y", y);
			visitor.visit("hp", hp);
			visitor.visit("spirit", spirit);
		}
	};
}
