#ifdef CPPCURL_EXPORTS
#define CPPCURL_API __declspec(dllexport)
#else
#define CPPCURL_API __declspec(dllimport)
#endif

#include <string>

// @param:
// encoded_image: 需要进行公式识别的图片非二进制数据. 图片数据需要base64编码并进行urlencode.
// access_token: 调用百度API需要的token.
// @return:
// 公式识别结果,json格式.
CPPCURL_API std::string formulaRecognition(const std::string& encoded_image, const std::string& access_token);

// @param:
// latex_string: 需要渲染的latex string. 注意删除所有空白字符.
// file_path: 下载渲染后图片的路径.
// format: 下载图片的格式. 支持gif, svg, png.
CPPCURL_API void downloadRenderedFormula(const std::string& latex_string, const std::string& file_path, const std::string& format);

// @param:
// latex_string: 需要渲染的latex string. 注意删除所有空白字符.
// format: 下载图片的格式. 支持gif, svg, png.
// @return:
// 下载的二进制文件. string是用来转移data的工具, 实际存储的是二进制data, *绝对*不要当作string使用.
// 需要使用该数据时请使用.c_str()获得data pointer.
CPPCURL_API std::string downloadRenderedFormula(const std::string& latex_string,const std::string& format);

// @param:
// file_path: 图像路径
// @return:
// 图像经过base64编码, urlencode后的string
CPPCURL_API std::string imageBase64UrlEncode(const std::string& file_path);


CPPCURL_API std::string imageBase64(const std::string& file_path, const std::string& image_format);


CPPCURL_API std::string formulaRecognitionMathpix(const std::string& encoded_image);