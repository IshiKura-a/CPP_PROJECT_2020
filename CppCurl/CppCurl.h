#pragma once
#include <string>

// @param:
// encoded_image: ��Ҫ���й�ʽʶ���ͼƬ�Ƕ���������. ͼƬ������Ҫbase64���벢����urlencode.
// access_token: ���ðٶ�API��Ҫ��token.
// @return:
// ��ʽʶ����,json��ʽ.
std::string formulaRecognition(const std::string& encoded_image, const std::string& access_token);

// @param:
// latex_string: ��Ҫ��Ⱦ��latex string. ע��ɾ�����пհ��ַ�.
// file_path: ������Ⱦ��ͼƬ��·��.
// format: ����ͼƬ�ĸ�ʽ. ֧��gif, svg, png.
void downloadRenderedFormula(const std::string& latex_string, const std::string& file_path, const std::string& format);

// @param:
// bytes_to_encode: ��Ҫ����������ݵ�ָ��.
// in_len: ��Ҫ����������ݵĳ���.
// @return:
// base64����������.
std::string base64Encode(const char* bytes_to_encode, unsigned int in_len);

// @param:
// encoded_string: base64��������ݵ�ָ��.
// @return:
// base64����������.
std::string base64Decode(const std::string & encoded_string);

// @param:
// bytes_to_encode: ��Ҫ����������ݵ�ָ��.
// @return:
// urlencode�������.
std::string urlEncode(const std::string& bytes_to_encode);

// @param:
// encoded_string: ��Ҫ����������ݵ�ָ��.
// @return:
// urldecode�������.
std::string urlDecode(const std::string& encoded_string);