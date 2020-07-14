#include "pch.h"
#include "CppCurl.h"
#include "HTTPRequestManager.h"

std::shared_ptr<IHTTPRequestManager> getHTTPRequestManager()
{
	return std::make_shared<HTTPRequestManager>();
}

RequestManager::RequestManager() :manager(getHTTPRequestManager())
{

}
