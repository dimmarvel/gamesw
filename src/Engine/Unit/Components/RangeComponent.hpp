#pragma once
#include "HealthComponent.hpp"
#include "IComponent.hpp"

namespace sw::engine
{
	class RangeComponent final : public IComponent
	{
	private:
		int range;

	public:
		explicit RangeComponent(int r) :
				range(r)
		{}

		inline int getRange() const noexcept
		{
			return range;
		}
	};
}
