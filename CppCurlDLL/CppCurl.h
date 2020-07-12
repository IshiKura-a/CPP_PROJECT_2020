#pragma once
#ifdef CPPCURL_EXPORTS
#define CPPCURL_API __declspec(dllexport)
#else
#define CPPCURL_API __declspec(dllimport)
#endif
#include <vector>
#include <string>
#include <memory>

class IHTTPRequestManager
{
	using Byte = char;
public:

	// @param:
	// raw_image: ��Ҫ���й�ʽʶ���ͼƬ������ԭʼ����.
	// @return:
	// ��ʽʶ����,json��ʽ.
	virtual std::string formulaRecognitionBaidu(const std::vector<Byte>& raw_image) = 0;

	// @param:
	// file_path: ��Ҫ���й�ʽʶ���ͼƬ·��.
	// @return:
	// ��ʽʶ����,json��ʽ.
	virtual std::string formulaRecognitionBaidu(const std::string& file_path) = 0;

	// @param:
	// raw_image: ��Ҫ���й�ʽʶ���ͼƬ������ԭʼ����.
	// image_format: ����������ͼƬ�ĸ�ʽ.
	// @return:
	// ��ʽʶ����,json��ʽ.
	virtual std::string formulaRecognitionMathpix(const std::vector<Byte>& raw_image, const std::string& image_format) = 0;

	// @param:
	// file_path: ��Ҫ���й�ʽʶ���ͼƬ·��.
	// @return:
	// ��ʽʶ����,json��ʽ.
	virtual std::string formulaRecognitionMathpix(const std::string& file_path) = 0;

	// @param:
	// latex_string: ��Ҫ��Ⱦ��latex string.
	// file_path: ������Ⱦ��ͼƬ��·��.
	// format: ����ͼƬ�ĸ�ʽ. ֧��gif, svg, png.
	virtual void downloadRenderedFormula(const std::string& latex_string, const std::string& file_path, const std::string& format) = 0;

	// @param:
	// latex_string: ��Ҫ��Ⱦ��latex string. ע��ɾ�����пհ��ַ�.
	// format: ����ͼƬ�ĸ�ʽ. ֧��gif, svg, png.
	// @return:
	// ���ص�ͼƬ�ļ��Ķ���������.
	virtual std::vector<Byte> downloadRenderedFormula(const std::string& latex_string, const std::string& format) = 0;

	// @param:
	// file_path: ͼƬ�ļ�·��.
	// @return:
	// ͼƬ�ļ��Ķ���������.
	virtual std::vector<Byte> openImage(const std::string& file_path) = 0;

	// @param:
	// data: ��Ҫ�����ͼƬ�Ķ���������.
	// file_path: �����·��.
	virtual void saveImage(const std::vector<Byte>& data, const std::string& file_path) = 0;

	virtual ~IHTTPRequestManager() = default;
};

std::shared_ptr<IHTTPRequestManager> getHTTPRequestManager();

CPPCURL_API class RequestManager
{
private:
	std::shared_ptr<IHTTPRequestManager> manager = getHTTPRequestManager();
public:
	CPPCURL_API RequestManager() = default;
	CPPCURL_API IHTTPRequestManager* operator->() const { return manager.get(); }
};
