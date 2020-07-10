#pragma once
#include <string>

// @param:
// encoded_image: 需要进行公式识别的图片非二进制数据. 图片数据需要base64编码并进行urlencode.
// access_token: 调用百度API需要的token.
// @return:
// 公式识别结果,json格式.
std::string formulaRecognition(const std::string& encoded_image, const std::string& access_token);

// @param:
// latex_string: 需要渲染的latex string. 注意删除所有空白字符.
// file_path: 下载渲染后图片的路径.
// format: 下载图片的格式. 支持gif, svg, png.
void downloadRenderedFormula(const std::string& latex_string, const std::string& file_path, const std::string& format);

// @param:
// bytes_to_encode: 需要被编码的数据的指针.
// in_len: 需要被编码的数据的长度.
// @return:
// base64编码后的数据.
std::string base64Encode(const char* bytes_to_encode, unsigned int in_len);

// @param:
// encoded_string: base64编码的数据的指针.
// @return:
// base64解码后的数据.
std::string base64Decode(const std::string & encoded_string);

// @param:
// bytes_to_encode: 需要被编码的数据的指针.
// @return:
// urlencode后的数据.
std::string urlEncode(const std::string& bytes_to_encode);

// @param:
// encoded_string: 需要被解码的数据的指针.
// @return:
// urldecode后的数据.
std::string urlDecode(const std::string& encoded_string);