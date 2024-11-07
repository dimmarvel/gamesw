#pragma once

#include <cstdint>
#include <iosfwd>

namespace sw::io
{
	struct SpawnSwordsman
	{
		constexpr static const char* Name = "SPAWN_SWORDSMAN";

		uint32_t unitId{};
		int x{};
		int y{};
		uint32_t hp{};
		uint32_t strength{};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("x", x);
			visitor.visit("y", y);
			visitor.visit("hp", hp);
			visitor.visit("strength", strength);
		}
	};
}
