#pragma once
#ifdef CPPCURL_EXPORTS
#define CPPCURL_API __declspec(dllexport)
#else
#define CPPCURL_API __declspec(dllimport)
#endif
#include <vector>
#include <string>

class IHTTPRequestManager
{
	using Byte = int8_t;
public:

	// @param:
	// raw_image: ��Ҫ���й�ʽʶ���ͼƬ������ԭʼ����.
	// access_token: ���ðٶ�API��Ҫ��token.
	// @return:
	// ��ʽʶ����,json��ʽ.
	virtual std::string formulaRecognitionBaidu(const std::vector<Byte>& raw_image, const std::string& access_token) = 0;

	// @param:
	// raw_image: ��Ҫ���й�ʽʶ���ͼƬ������ԭʼ����.
	// @return:
	// ��ʽʶ����,json��ʽ.
	virtual std::string formulaRecognitionMathpix(const std::vector<Byte>& raw_image) = 0;

	// @param:
	// latex_string: ��Ҫ��Ⱦ��latex string. ע��ɾ�����пհ��ַ�.
	// file_path: ������Ⱦ��ͼƬ��·��.
	// format: ����ͼƬ�ĸ�ʽ. ֧��gif, svg, png.
	virtual void downloadRenderedFormula(const std::string& latex_string, const std::string& file_path, const std::string& format) = 0;

	// @param:
	// latex_string: ��Ҫ��Ⱦ��latex string. ע��ɾ�����пհ��ַ�.
	// format: ����ͼƬ�ĸ�ʽ. ֧��gif, svg, png.
	// @return:
	// ���صĶ������ļ�.
	virtual std::vector<Byte> downloadRenderedFormula(const std::string& latex_string, const std::string& format) = 0;

	virtual std::vector<Byte> openImage(const std::string& file_path) = 0;

	virtual ~IHTTPRequestManager() = default;
};


[[nodiscard]] CPPCURL_API IHTTPRequestManager* getHTTPRequestManager();
