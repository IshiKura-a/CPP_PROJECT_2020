#pragma once
#include <curl/curl.h>
#include <string>

void url_link(CURL* curl, std::string url_base, std::string encoded_token);