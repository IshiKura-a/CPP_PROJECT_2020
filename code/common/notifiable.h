#pragma once
#include "def.h"
#include <vector>

using EventId = int8_t;
constexpr EventId EventUnregistered = 0;

class Notifiable
{
private:
	static EventFunction unregistered;
	static std::vector<EventFunction> events;
	static EventId idRegistrar;
	static EventId getEventId();
public:
	static EventId registerEvent(EventFunction event)
	{
		EventId id = getEventId();
		events.push_back(event);
		return id;
	}
	static void raiseEvent(EventId id) noexcept(false)
	{
		events[id]();
	}
	virtual ~Notifiable() = 0;
};