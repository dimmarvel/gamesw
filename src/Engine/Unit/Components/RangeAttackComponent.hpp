#pragma once
#include "RangeComponent.hpp"

namespace sw::engine
{
	class RangeAttackComponent final : public RangeComponent
	{
	public:
		explicit RangeAttackComponent(int min_r, int max_r) :
			RangeComponent(min_r, max_r)
		{}
	};
}
