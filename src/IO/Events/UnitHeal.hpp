#pragma once

#include <cstdint>
#include <string>

namespace sw::io
{
	struct UnitHeal
	{
		constexpr static const char* Name = "UNIT_HEAL";

		uint32_t unitTargetId{};
		uint32_t unitHealerId{};
		uint32_t healingAmount{};
		uint32_t targetHpAmount{};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitTargetId", unitTargetId);
			visitor.visit("unitHealerId", unitHealerId);
			visitor.visit("healingAmount", healingAmount);
			visitor.visit("targetHpAmount", targetHpAmount);
		}
	};
}
