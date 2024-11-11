#pragma once
#include "HealthComponent.hpp"
#include "IComponent.hpp"

namespace sw::engine
{
	class RangeComponent : public IComponent
	{
	private:
		int min_range;
		int max_range;

	public:
		explicit RangeComponent(int min_r, int max_r) :
				min_range(min_r),
				max_range(max_r)
		{}

		inline int getMinRange() const noexcept
		{
			return min_range;
		}

		inline int getMaxRange() const noexcept
		{
			return max_range;
		}
	};
}
