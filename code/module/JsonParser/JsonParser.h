#pragma once
#include <rapidjson/rapidjson.h>
#include <string>

class JsonParser
{
public:
	std::string parseCurlReturnVal(std::string json,std::string API);
	std::string parseCurlReturnValBaidu(std::string json);
	std::string parseCurlReturnValMathpix(std::string json);
	virtual ~JsonParser() = 0;
};

