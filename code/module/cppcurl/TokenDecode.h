#pragma once
#ifdef TOKENDECODE_EXPORTS
#define TOKENDECODE_API __declspec(dllexport)
#else
#define TOKENDECODE_API __declspec(dllimport)
#endif

#include <curl/curl.h>
#include <string>

TOKENDECODE_API void url_link(CURL* curl, std::string url_base, std::string encoded_token);