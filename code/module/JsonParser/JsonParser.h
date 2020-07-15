#pragma once
#include <string>

class JsonParser
{
public:
	// @param:
	// json: json字符串, 不检查格式正确性
	// API: API名, 接受baidu, mathpix
	// @return
	// json中的latex string
	static std::string parseCurlReturnVal(const std::string& json, std::string API) noexcept(false);

	// @param:
	// json: json字符串, 不检查格式正确性
	// @return
	// json中的latex string
	static std::string parseCurlReturnValBaidu(const std::string& json) noexcept(false);

	// @param:
	// json: json字符串, 不检查格式正确性
	// @return
	// json中的latex string
	static std::string parseCurlReturnValMathpix(const std::string& json) noexcept(false);
	virtual ~JsonParser() = 0;
};

