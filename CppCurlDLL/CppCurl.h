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
	// raw_image: 需要进行公式识别的图片二进制原始数据.
	// access_token: 调用百度API需要的token.
	// @return:
	// 公式识别结果,json格式.
	virtual std::string formulaRecognitionBaidu(const std::vector<Byte>& raw_image, const std::string& access_token) = 0;

	// @param:
	// raw_image: 需要进行公式识别的图片二进制原始数据.
	// @return:
	// 公式识别结果,json格式.
	virtual std::string formulaRecognitionMathpix(const std::vector<Byte>& raw_image) = 0;

	// @param:
	// latex_string: 需要渲染的latex string. 注意删除所有空白字符.
	// file_path: 下载渲染后图片的路径.
	// format: 下载图片的格式. 支持gif, svg, png.
	virtual void downloadRenderedFormula(const std::string& latex_string, const std::string& file_path, const std::string& format) = 0;

	// @param:
	// latex_string: 需要渲染的latex string. 注意删除所有空白字符.
	// format: 下载图片的格式. 支持gif, svg, png.
	// @return:
	// 下载的二进制文件.
	virtual std::vector<Byte> downloadRenderedFormula(const std::string& latex_string, const std::string& format) = 0;

	virtual std::vector<Byte> openImage(const std::string& file_path) = 0;

	virtual ~IHTTPRequestManager() = default;
};


[[nodiscard]] CPPCURL_API IHTTPRequestManager* getHTTPRequestManager();
