#pragma once
#include <string>

class JsonParser
{
public:
	// @param:
	// json: json�ַ���, ������ʽ��ȷ��
	// API: API��, ����baidu, mathpix
	// @return
	// json�е�latex string
	static std::string parseCurlReturnVal(const std::string& json, std::string API) noexcept(false);

	// @param:
	// json: json�ַ���, ������ʽ��ȷ��
	// @return
	// json�е�latex string
	static std::string parseCurlReturnValBaidu(const std::string& json) noexcept(false);

	// @param:
	// json: json�ַ���, ������ʽ��ȷ��
	// @return
	// json�е�latex string
	static std::string parseCurlReturnValMathpix(const std::string& json) noexcept(false);
	virtual ~JsonParser() = 0;
};

