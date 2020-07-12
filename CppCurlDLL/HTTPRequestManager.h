#pragma once
#include "CppCurl.h"

class HTTPRequestManager : public IHTTPRequestManager
{
	using Byte = char;
private:
	const static std::string baidu_request_url;

	const static std::string mathpix_request_url;

	const static std::string latex_rendering_request_url;

	std::string formula_result;

	std::string render_result;

	
	
public:
	std::string formulaRecognitionBaidu(const std::vector<Byte>& encoded_image, const std::string& access_token) override;

	std::string formulaRecognitionMathpix(const std::vector<Byte>& raw_image, const std::string& image_format) override;

	std::vector<Byte> downloadRenderedFormula(const std::string& latex_string, const std::string& format) override;

	void downloadRenderedFormula(const std::string& latex_string, const std::string& file_path, const std::string& format) override;

	std::vector<Byte> openImage(const std::string& file_path) override;
	
	// @param:
	// file_path: 图像路径
	// @return:
	// 图像经过base64编码, urlencode后的string
	std::vector<Byte> imageBase64UrlEncode(const std::string& file_path);

};

