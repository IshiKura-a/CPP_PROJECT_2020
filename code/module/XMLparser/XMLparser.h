#pragma once
#include <string>

class XMLParser
{
public:
	// @param:
	// xml: xml�ַ���, ������ʽ��ȷ��
	// @return
	// xml�е�result
	static std::string parseCurlResult(const std::string& xml) noexcept(false);

	virtual ~XMLParser() = 0;
};

