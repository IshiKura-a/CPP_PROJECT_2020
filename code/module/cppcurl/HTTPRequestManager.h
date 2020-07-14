#pragma once
#include "CppCurl.h"

class HTTPRequestManager : public IHTTPRequestManager
{
	using Byte = char;
private:
	const static std::string baidu_request_url;
	const static std::string mathpix_request_url;
	const static std::string latex_rendering_request_url;
	const static std::string access_token;

	static std::string formula_result;
	static std::vector<Byte> render_result;

	// @param:
	// file_path: 图像路径
	// @return:
	// 图像经过base64编码, url encode后的string
	std::string imageBase64UrlEncode(const std::string& file_path);

	// @param:
	// raw_image: 图像二进制数据
	// @return:
	// 图像经过base64编码, url encode后的string
	std::string imageBase64UrlEncode(const std::vector<Byte>& raw_image);

	// @param:
	// file_path: 图像路径
	// @return:
	// 图像经过base64编码, 符合data url scheme的string
	std::string imageBase64DataUrlScheme(const std::string& file_path);

	// @param:
	// file_path: 图像二进制数据
	// @return:
	// 图像经过base64编码, 符合data url scheme的string
	std::string imageBase64DataUrlScheme(const std::vector<Byte>& raw_image, const std::string& image_format);


	// libcurl用到的回调函数. 回调函数必须是静态的。

	friend size_t callbackWriteFile(void* ptr, size_t size, size_t nmemb, void* stream);

	friend size_t callbackWriteFormulaResult(void* ptr, size_t size, size_t nmemb, void* stream);

	friend size_t callbackWriteRenderResult(void* ptr, size_t size, size_t nmemb, void* stream);

public:
	std::string formulaRecognitionBaidu(const std::vector<Byte>& encoded_image) override;

	std::string formulaRecognitionBaidu(const std::string& file_path) override;

	std::string formulaRecognitionMathpix(const std::vector<Byte>& raw_image, const std::string& image_format) override;

	std::string formulaRecognitionMathpix(const std::string& file_path) override;

	std::vector<Byte> downloadRenderedFormula(const std::string& latex_string, const std::string& format) override;

	void downloadRenderedFormula(const std::string& latex_string, const std::string& file_path, const std::string& format) override;

	std::vector<Byte> openImage(const std::string& file_path) override;

	void saveImage(const std::vector<Byte>& data, const std::string& file_path) override;
};

