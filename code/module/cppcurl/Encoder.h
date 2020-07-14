#pragma once
#include <string>

// @param:
// bytes_to_encode: 需要被编码的数据的指针.
// in_len: 需要被编码的数据的长度.
// @return:
// base64编码后的数据.
std::string base64Encode(const char* bytes_to_encode, unsigned int in_len);

// @param:
// encoded_string: base64编码的数据.
// @return:
// base64解码后的数据.
// !未测试
std::string base64Decode(const std::string & encoded_string);

// @param:
// bytes_to_encode: 需要被编码的数据.
// @return:
// urlencode后的数据.
std::string urlEncode(const std::string& bytes_to_encode);

// @param:
// encoded_string: 需要被解码的数据.
// @return:
// urldecode后的数据.
// !未测试
std::string urlDecode(const std::string& encoded_string);

// @param:
// file_path: 图像路径
// @return:
// 图像经过base64编码, urlencode后的string
std::string imageBase64UrlEncode(const std::string& file_path);