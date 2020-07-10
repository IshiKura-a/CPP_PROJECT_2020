#pragma once
#include <string>

// @param:
// bytes_to_encode: ��Ҫ����������ݵ�ָ��.
// in_len: ��Ҫ����������ݵĳ���.
// @return:
// base64����������.
std::string base64Encode(const char* bytes_to_encode, unsigned int in_len);

// @param:
// encoded_string: base64���������.
// @return:
// base64����������.
// !δ����
std::string base64Decode(const std::string & encoded_string);

// @param:
// bytes_to_encode: ��Ҫ�����������.
// @return:
// urlencode�������.
std::string urlEncode(const std::string& bytes_to_encode);

// @param:
// encoded_string: ��Ҫ�����������.
// @return:
// urldecode�������.
// !δ����
std::string urlDecode(const std::string& encoded_string);

// @param:
// file_path: ͼ��·��
// @return:
// ͼ�񾭹�base64����, urlencode���string
std::string imageBase64UrlEncode(const std::string& file_path);