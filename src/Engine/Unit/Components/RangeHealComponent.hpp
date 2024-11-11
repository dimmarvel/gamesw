#pragma once
#include "RangeComponent.hpp"

namespace sw::engine
{
	class RangeHealComponent final : public RangeComponent
	{
	public:
		explicit RangeHealComponent(int min_r, int max_r) :
			RangeComponent(min_r, max_r)
		{}
	};
}
