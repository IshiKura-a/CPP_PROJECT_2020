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
	// raw_image: 需要进行公式识别的图片二进制原始数据.
	// @return:
	// 公式识别结果, json格式.
	// @throw:
	// curl初始化若产生错误, 则抛出runtime_error
	[[nodiscard]] virtual std::string formulaRecognitionBaidu(const std::vector<Byte>& raw_image) noexcept(false) = 0;

	// @param:
	// file_path: 需要进行公式识别的图片路径.
	// @return:
	// 公式识别结果,json格式.
	// @throw:
	// curl初始化若产生错误, 则抛出runtime_error
	// 读取文件若产生错误, 则抛出runtime_error
	[[nodiscard]] virtual std::string formulaRecognitionBaidu(const std::string& file_path) noexcept(false) = 0;

	// @param:
	// raw_image: 需要进行公式识别的图片二进制原始数据.
	// image_format: 二进制数据图片的格式.
	// @return:
	// 公式识别结果,json格式.
	// @throw:
	// curl初始化若产生错误, 则抛出runtime_error
	[[nodiscard]] virtual std::string formulaRecognitionMathpix(const std::vector<Byte>& raw_image, const std::string& image_format) noexcept(false) = 0;

	// @param:
	// file_path: 需要进行公式识别的图片路径.
	// @return:
	// 公式识别结果,json格式.
	// @throw:
	// curl初始化若产生错误, 则抛出runtime_error
	// 读取文件若产生错误, 则抛出runtime_error
	[[nodiscard]] virtual std::string formulaRecognitionMathpix(const std::string& file_path) noexcept(false) = 0;

	// @param:
	// latex_string: 需要渲染的latex string.
	// file_path: 下载渲染后图片的路径.
	// format: 下载图片的格式. 支持gif, svg, png.
	// @throw:
	// curl初始化若产生错误, 则抛出runtime_error
	virtual void downloadRenderedFormula(const std::string& latex_string, const std::string& file_path, const std::string& format) noexcept(false) = 0;

	// @param:
	// latex_string: 需要渲染的latex string. 注意删除所有空白字符.
	// format: 下载图片的格式. 支持gif, svg, png.
	// @return:
	// 下载的图片文件的二进制数据.
	// @throw:
	// curl初始化若产生错误, 则抛出runtime_error
	// 读取文件若产生错误, 则抛出runtime_error
	[[nodiscard]] virtual std::vector<Byte> downloadRenderedFormula(const std::string& latex_string, const std::string& format) noexcept(false) = 0;

	// @param:
	// latex_string: 需要计算的latex string.
	// @return:
	// 计算结果, xml格式
	// @throw:
	// curl初始化若产生错误, 则抛出runtime_error
	[[nodiscard]] virtual std::string getFormulaResult(const std::string& latex_string) noexcept(false) = 0;

	// @param:
	// file_path: 图片文件路径.
	// @return:
	// 图片文件的二进制数据.
	// @throw:
	// 读取文件若产生错误, 则抛出runtime_error
	[[nodiscard]] virtual std::vector<Byte> openImage(const std::string& file_path) noexcept(false) = 0;

	// @param:
	// data: 需要保存的图片的二进制数据.
	// file_path: 保存的路径.
	// @throw:
	// 读取文件若产生错误, 则抛出runtime_error
	virtual void saveImage(const std::vector<Byte>& data, const std::string& file_path) noexcept(false) = 0;

	virtual ~IHTTPRequestManager() = default;
};

class CPPCURL_API RequestManager
{
private:
	std::shared_ptr<IHTTPRequestManager> manager;
public:
	RequestManager();
	IHTTPRequestManager* operator->() const { return manager.get(); }
};
