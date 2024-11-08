#pragma once

#include "details/PrintFieldVisitor.hpp"
#include <iostream>
#include <typeindex>
#include <Engine/Core/Tick.hpp>

namespace sw
{
	class EventLog
	{
	public:
		EventLog(const EventLog&) = delete;
		EventLog& operator=(const EventLog&) = delete;

		static EventLog& get() {
			static EventLog instance;
			return instance;
		}

		template <class TEvent>
		void log(TEvent&& event) {
			std::cout << "[" << engine::Tick::get().getTick() << "] " << TEvent::Name << " ";
			PrintFieldVisitor visitor(std::cout);
			event.visit(visitor);
			std::cout << std::endl;
		}

	private:
		EventLog() {}
	};
}
