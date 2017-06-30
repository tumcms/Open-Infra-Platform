#pragma once

#include <utility>

namespace carve
{
	namespace _vs2013
	{
		template<typename TFirst, typename TSecond>
		struct pair_hash final
		{
		public:
			size_t operator()(const std::pair<TFirst, TSecond>& value) const
			{
				size_t first = std::hash<TFirst>()(value.first);
				size_t second = std::hash<TSecond>()(value.second);
				return first ^ ((second << 24) | (second >> 8));
			}
		};
	}
}
