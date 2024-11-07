#pragma once

#include <cstdint>
#include <iosfwd>

namespace sw::io
{
	struct CreateMap
	{
		constexpr static const char* Name = "CREATE_MAP";

		int width{};
		int height{};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("width", width);
			visitor.visit("height", height);
		}
	};
}
