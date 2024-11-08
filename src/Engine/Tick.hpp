#pragma once
#include <atomic>

namespace sw::engine
{
	/**
	 * @class Tick
	 * @brief Singleton class for managing the game's tick counter.
	 * 
	 * The `Tick` class provides a mechanism for tracking the passage of time within the game,
	 * using a counter that increments with each "tick." This class follows the singleton pattern,
	 * ensuring there is only one instance of `Tick` throughout the game.
	 * 
	 * The tick counter is managed atomically, allowing it to be safely accessed and updated
	 * in a multi-threaded environment.
	 */
	class Tick
	{
	public:
		Tick(const Tick&) = delete;
		Tick& operator=(const Tick&) = delete;

		static Tick& get() {
			static Tick instance;
			return instance;
		}

		uint64_t getTick() const {
			return tick.load(std::memory_order_relaxed);
		}

		uint64_t incrementTick() {
			return tick.fetch_add(1, std::memory_order_relaxed);
		}

	private:
		Tick() : tick(0) {}
		std::atomic<uint64_t> tick;
	};
}