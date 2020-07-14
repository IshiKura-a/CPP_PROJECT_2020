#pragma once
#include "def.h"
#include <vector>

using EventId = int8_t;
constexpr EventId EventUnregistered = 0;

class Notifiable
{
private:
	static CallbackFunction unregistered;
	static std::vector<CallbackFunction> events;
	static EventId idRegistrar;
	static EventId getEventId();
public:
	// 注册事件
	// @param
	// event: 事件对应的回调函数
	// @return
	// 被注册事件的ID
	static EventId registerEvent(CallbackFunction event)
	{
		EventId id = getEventId();
		events.push_back(event);
		return id;
	}
	// 注销事件
	// @param
	// id: 需要注销的事件的id
	static void unregisterEvent(EventId id)
	{
		events.at(id) = unregistered;
	}
	// 触发事件注册的回调函数
	// @param
	// id: 事件的ID
	static void raiseEvent(EventId id) noexcept(false)
	{
		events[id]();
	}
	virtual ~Notifiable() = 0;
};