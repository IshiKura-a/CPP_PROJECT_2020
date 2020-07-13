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
	// ע���¼�
	// @param
	// event: �¼���Ӧ�Ļص�����
	// @return
	// ��ע���¼���ID
	static EventId registerEvent(CallbackFunction event)
	{
		EventId id = getEventId();
		events.push_back(event);
		return id;
	}
	// ע���¼�
	// @param
	// id: ��Ҫע�����¼���id
	static void unregisterEvent(EventId id)
	{
		events.at(id) = unregistered;
	}
	// �����¼�ע��Ļص�����
	// @param
	// id: �¼���ID
	static void raiseEvent(EventId id) noexcept(false)
	{
		events[id]();
	}
	virtual ~Notifiable() = 0;
};