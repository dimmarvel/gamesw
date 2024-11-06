#pragma once
#include <atomic>

namespace sw::engine
{
	// It's not a good idea to keep a tick in singleton and get it for every event.
	// In a multithreaded environment it will be a pain.
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