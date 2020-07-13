#include "notifiable.h"
#include <stdexcept>


CallbackFunction Notifiable::unregistered = []() {throw std::runtime_error("Calling unregistered event"); };

// unregistered at 0
std::vector<CallbackFunction> Notifiable::events(1, Notifiable::unregistered);

EventId Notifiable::idRegistrar = 1;

EventId Notifiable::getEventId()
{
	return idRegistrar++;
}

Notifiable::~Notifiable() = default;
