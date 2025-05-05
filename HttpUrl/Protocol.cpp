#include "Protocol.h"

const Protocol Protocol::HTTP(Protocol::Enum::HTTP);
const Protocol Protocol::HTTPS(Protocol::Enum::HTTPS);

Protocol::Protocol()
	: m_value(Enum::HTTP)
{
}

const char* Protocol::ToString() const
{
	return m_value == Enum::HTTP
		? "http"
		: "https";
}

Protocol::operator Enum() const
{
	return m_value;
}

Protocol::Protocol(Enum value)
	: m_value(value)
{
}
