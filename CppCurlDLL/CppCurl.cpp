#include "pch.h"
#include "CppCurl.h"
#include "HTTPRequestManager.h"

[[nodiscard]] CPPCURL_API IHTTPRequestManager* getHTTPRequestManager()
{
	return new HTTPRequestManager();
}
