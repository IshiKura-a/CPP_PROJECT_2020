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
	static std::string parseCurlReturnVal(std::string json,std::string API) noexcept(false);

	// @param:
	// json: json�ַ���, ������ʽ��ȷ��
	// @return
	// json�е�latex string
	static std::string parseCurlReturnValBaidu(std::string json) noexcept(false);

	// @param:
	// json: json�ַ���, ������ʽ��ȷ��
	// @return
	// json�е�latex string
	static std::string parseCurlReturnValMathpix(std::string json) noexcept(false);
	virtual ~JsonParser() = 0;
};

