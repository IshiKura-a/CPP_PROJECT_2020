#pragma once
#include <string>

class XMLParser
{
public:
	// @param:
	// xml: xml字符串, 不检查格式正确性
	// @return
	// xml中的result
	static std::string parseCurlResult(const std::string& xml) noexcept(false);

	virtual ~XMLParser() = 0;
};

