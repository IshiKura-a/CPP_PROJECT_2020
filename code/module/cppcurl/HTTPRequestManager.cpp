#include "pch.h"
#include "HTTPRequestManager.h"
#include "TokenDecode.h"
#include <curl/curl.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <cassert>

using Byte = char;

const std::string HTTPRequestManager::baidu_request_url = "https://aip.baidubce.com/rest/2.0/ocr/v1/formula";

const std::string HTTPRequestManager::mathpix_request_url = "https://api.mathpix.com/v3/latex";

const std::string HTTPRequestManager::latex_rendering_request_url = "https://latex.codecogs.com/";

const std::string HTTPRequestManager::formula_calculate_request_url = "http://api.wolframalpha.com/v2/query";

std::string HTTPRequestManager::formula_result;

std::vector<Byte> HTTPRequestManager::render_result;

std::string HTTPRequestManager::calculate_result;

const std::string HTTPRequestManager::access_token = "7A4F0C7C6D1AA836183C6245AF5A546D\
CA62994D2AD6DF01083A5170573825F8\
869CE35BD9C4A5770C63CCD9A59CBE5B\
D63F06E28A2AA8D4251B7222F3DC52BE\
CACE6DD82CDB6F51353347977A16371B";

std::string urlEncode(const std::string& bytes_to_encode);

size_t callbackWriteFile(void* ptr, size_t size, size_t nmemb, void* stream)
{
	fwrite(ptr, size, nmemb, static_cast<FILE*>(stream));
	return size * nmemb;
}

size_t callbackWriteFormulaResult(void* ptr, size_t size, size_t nmemb, void* stream)
{
	// 经过测试, 多次传输中只有最后一次传输会传送相应的latex string json, 在此之前都是传输http header
	HTTPRequestManager::formula_result = std::string(static_cast<char*>(ptr), size * nmemb);
	return size * nmemb;
}

size_t callbackWriteRenderResult(void* ptr, size_t size, size_t nmemb, void* stream)
{
	// !HACK
	// 图片文件极有可能多次传输, 需要拼合
	auto tmp = std::vector<Byte>(static_cast<char*>(ptr), static_cast<char*>(ptr) + size * nmemb);
	HTTPRequestManager::render_result.insert(HTTPRequestManager::render_result.end(), tmp.begin(), tmp.end());
	return size * nmemb;
}

size_t callbackWriteCalculateResult(void* ptr, size_t size, size_t nmemb, void* stream)
{
	HTTPRequestManager::calculate_result = std::string(static_cast<char*>(ptr), size * nmemb);
	return size * nmemb;
}

std::string HTTPRequestManager::formulaRecognitionBaidu(const std::vector<Byte>& raw_image)
{

	// 返回公式识别的结果字符串
	// 如果curl的初始化过程中产生错误，抛出runtime_error
	// 百度的服务器端产生的错误不会抛出异常，但返回的json string有错误信息

	CURL* curl = NULL;
	curl_slist* headerlist = NULL;
	CURLcode result_code;


	std::string encoded_image = imageBase64UrlEncode(raw_image);

	encoded_image = "image=" + encoded_image;

	curl = curl_easy_init();

	if (curl) {

		// https抓包使用
		//curl_easy_setopt(curl, CURLOPT_PROXY, "127.0.0.1:8888");

		// header设置，似乎可以省略
		headerlist = curl_slist_append(headerlist, "Content-Type:application/x-www-form-urlencoded");

		// 打印调试信息
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		// URL地址，加密访问
		url_link(curl, baidu_request_url, access_token);
		// 设置POST内容，内容指针encoded_image为char*，注意字符串中要带上表单名称image=
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, encoded_image.c_str());
		// 绑定header
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
		// 设置写函数
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackWriteFormulaResult);
		// 设置本次操作为POST
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		// 设置本次操作使用header
		curl_easy_setopt(curl, CURLOPT_HEADER, 1);
		// 设置callback函数的第四个参数为data_ptr
		//curl_easy_setopt(curl,CURLOPT_WRITEDATA,data_ptr);

		result_code = curl_easy_perform(curl);
		if (result_code != CURLE_OK)
		{
			std::string errmsg = "curl_easy_perform() failed.";
			errmsg = errmsg + curl_easy_strerror(result_code);
			curl_easy_cleanup(curl);
			throw std::runtime_error(errmsg);
		}

		curl_easy_cleanup(curl);

		return std::move(formula_result);
	}
	else
	{
		throw std::runtime_error("curl_easy_init() failed.");
	}
}

std::string HTTPRequestManager::formulaRecognitionBaidu(const std::string& file_path)
{
	return formulaRecognitionBaidu(openImage(file_path));
}


std::string HTTPRequestManager::formulaRecognitionMathpix(const std::vector<Byte>& raw_image, const std::string& image_format)
{

	// 返回公式识别的结果字符串
	// 如果curl的初始化过程中产生错误，抛出runtime_error
	// mathpix的服务器端产生的错误不会抛出异常，但返回的json string有错误信息

	CURL* curl = NULL;
	std::string url = mathpix_request_url;
	curl_slist* headerlist = NULL;
	CURLcode result_code;

	std::string encoded_image = imageBase64DataUrlScheme(raw_image, image_format);


	curl = curl_easy_init();

	if (curl) {

		// header设置
		headerlist = curl_slist_append(headerlist, "Content-Type:application/json");
		headerlist = curl_slist_append(headerlist, "app_id:tmp_key");
		headerlist = curl_slist_append(headerlist, "app_key:ey4fCTFxcjJ3kqbEaH7j23b926HBAux3a98");

		rapidjson::StringBuffer buffer;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
		writer.StartObject();

		writer.Key("src");
		writer.String(encoded_image.c_str(), encoded_image.size());

		writer.Key("formats");
		writer.StartArray();
		//writer.String("latex_normal");
		//writer.String("latex_styled");
		writer.String("latex_simplified");
		writer.EndArray();

		writer.EndObject();

		std::string json_content = buffer.GetString();

		// 打印调试信息
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		// URL地址
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		// 设置POST内容，内容指针encoded_image为char*，注意字符串中要带上表单名称image=
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_content.c_str());
		// 绑定header
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
		// 设置写函数
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackWriteFormulaResult
		);
		// 设置本次操作为POST
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		// 设置本次操作使用header
		curl_easy_setopt(curl, CURLOPT_HEADER, 1);
		// 设置callback函数的第四个参数为data_ptr
		//curl_easy_setopt(curl,CURLOPT_WRITEDATA,data_ptr);

		result_code = curl_easy_perform(curl);
		if (result_code != CURLE_OK)
		{
			std::string errmsg = "curl_easy_perform() failed.";
			errmsg = errmsg + curl_easy_strerror(result_code);
			curl_easy_cleanup(curl);
			throw std::runtime_error(errmsg);
		}

		curl_easy_cleanup(curl);

		return std::move(formula_result);
	}
	else
	{
		throw std::runtime_error("curl_easy_init() failed.");
	}
}

std::string HTTPRequestManager::formulaRecognitionMathpix(const std::string& file_path)
{
	auto data = openImage(file_path);
	auto format = file_path.substr(file_path.find_last_of('.') + 1);
	if (format == "jpg") format = "jpeg";
	return formulaRecognitionMathpix(data, format);
}


void HTTPRequestManager::downloadRenderedFormula(const std::string& latex_string, const std::string& file_path, const std::string& format)
{
	std::string url_encoded_latex_string = urlEncode(latex_string);
	std::string url = latex_rendering_request_url + format + ".download?\\dpi{600}" + url_encoded_latex_string;

	CURL* curl = NULL;
	CURLcode result_code;

	FILE* fp = NULL;
	fopen_s(&fp, file_path.c_str(), "wb");

	if (!fp)
		throw std::runtime_error("Cannot open image file " + file_path);

	curl = curl_easy_init();

	if (curl) {

		// 打印调试信息
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		// URL地址，需要char*
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		// 设置写函数
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackWriteFile);
		// 设置写函数写入的指针
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

		result_code = curl_easy_perform(curl);
		if (result_code != CURLE_OK)
		{
			std::string errmsg = "curl_easy_perform() failed.";
			errmsg = errmsg + curl_easy_strerror(result_code);
			curl_easy_cleanup(curl);
			throw std::runtime_error(errmsg);
		}
		fclose(fp);
		curl_easy_cleanup(curl);
	}
	else
	{
		throw std::runtime_error("curl_easy_init() failed.");
	}
}

std::vector<Byte> HTTPRequestManager::downloadRenderedFormula(const std::string& latex_string, const std::string& format)
{
	std::string url_encoded_latex_string = urlEncode(latex_string);
	std::string url = latex_rendering_request_url + format + ".download?\\dpi{600}" + url_encoded_latex_string;

	CURL* curl = NULL;
	CURLcode result_code;

	curl = curl_easy_init();

	if (curl) {

		// 打印调试信息
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		// URL地址，需要char*
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		// 设置写函数
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackWriteRenderResult);

		result_code = curl_easy_perform(curl);
		if (result_code != CURLE_OK)
		{
			std::string errmsg = "curl_easy_perform() failed.";
			errmsg = errmsg + curl_easy_strerror(result_code);
			curl_easy_cleanup(curl);
			throw std::runtime_error(errmsg);
		}
		curl_easy_cleanup(curl);
		return std::move(render_result);
	}
	else
	{
		throw std::runtime_error("curl_easy_init() failed.");
	}
}

std::string HTTPRequestManager::getFormulaResult(const std::string& latex_string)
{
	std::string url_encoded_latex_string = urlEncode(latex_string);
	std::string url = formula_calculate_request_url + "?appid=3YG4PV-RWY3K2Y7P8&format=plaintext&includepodid=result&input=" + url_encoded_latex_string;
	CURL* curl = NULL;
	CURLcode result_code;


	curl = curl_easy_init();

	if (curl) {
		// 打印调试信息
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		// 设置写函数
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackWriteCalculateResult);

		result_code = curl_easy_perform(curl);
		if (result_code != CURLE_OK)
		{
			std::string errmsg = "curl_easy_perform() failed.";
			errmsg = errmsg + curl_easy_strerror(result_code);
			curl_easy_cleanup(curl);
			throw std::runtime_error(errmsg);
		}

		curl_easy_cleanup(curl);

		return std::move(calculate_result);
	}
	else
	{
		throw std::runtime_error("curl_easy_init() failed.");
	}
}


// helper function

static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


static bool isBase64(const char c)
{
	return (isalnum(c) || (c == '+') || (c == '/'));
}

// @param:
// bytes_to_encode: 需要被编码的数据的指针.
// in_len: 需要被编码的数据的长度.
// @return:
// base64编码后的数据.
std::string base64Encode(const char* bytes_to_encode, unsigned int in_len)
{
	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--)
	{
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3)
		{
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;
			for (i = 0; (i < 4); i++)
			{
				ret += base64_chars[char_array_4[i]];
			}
			i = 0;
		}
	}
	if (i)
	{
		for (j = i; j < 3; j++)
		{
			char_array_3[j] = '\0';
		}

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
		{
			ret += base64_chars[char_array_4[j]];
		}

		while ((i++ < 3))
		{
			ret += '=';
		}

	}
	return ret;
}

// @param:
// encoded_string: base64编码的数据.
// @return:
// base64解码后的数据.
// !未测试
std::string base64Decode(const std::string& encoded_string)
{
	int in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string ret;

	while (in_len-- && (encoded_string[in_] != '=') && isBase64(encoded_string[in_])) {
		char_array_4[i++] = encoded_string[in_]; in_++;
		if (i == 4) {
			for (i = 0; i < 4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}
	if (i) {
		for (j = i; j < 4; j++)
			char_array_4[j] = 0;

		for (j = 0; j < 4; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
	}

	return ret;
}


unsigned char decToHex(unsigned char x)
{
	return  x > 9 ? x + 55 : x + 48;
}

unsigned char hexToDec(unsigned char x)
{
	unsigned char y;
	if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
	else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
	else if (x >= '0' && x <= '9') y = x - '0';
	else assert(0);
	return y;
}

// @param:
// bytes_to_encode: 需要被编码的数据.
// @return:
// urlencode后的数据.
std::string urlEncode(const std::string& bytes_to_encode)
{
	std::string strTemp = "";
	size_t length = bytes_to_encode.length();
	for (size_t i = 0; i < length; i++)
	{
		if (isalnum(bytes_to_encode[i]) ||
			(bytes_to_encode[i] == '-') ||
			(bytes_to_encode[i] == '_') ||
			(bytes_to_encode[i] == '.') ||
			(bytes_to_encode[i] == '~'))
			strTemp += bytes_to_encode[i];
		else if (bytes_to_encode[i] == ' ')
		{
			// strTemp += "+";
			strTemp += "%20";
		}	
		else
		{
			strTemp += '%';
			strTemp += decToHex(bytes_to_encode[i] >> 4);
			strTemp += decToHex(bytes_to_encode[i] % 16);
		}
	}
	return strTemp;
}

// @param:
// encoded_string: 需要被解码的数据.
// @return:
// urldecode后的数据.
// !未测试
std::string urlDecode(const std::string& encoded_string)
{
	std::string strTemp = "";
	size_t length = encoded_string.length();
	for (size_t i = 0; i < length; i++)
	{
		if (encoded_string[i] == '+') strTemp += ' ';
		else if (encoded_string[i] == '%')
		{
			assert(i + 2 < length);
			unsigned char high = hexToDec(encoded_string[++i]);
			unsigned char low = hexToDec(encoded_string[++i]);
			strTemp += static_cast<unsigned char>(high * 16 + low);
		}
		else strTemp += encoded_string[i];
	}
	return strTemp;
}

std::vector<Byte> HTTPRequestManager::openImage(const std::string& file_path)
{
	FILE* fp = NULL;
	fopen_s(&fp, file_path.c_str(), "rb");

	if (!fp)
		throw std::runtime_error("Cannot open image file " + file_path);

	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	rewind(fp);

	auto retVal = std::vector<Byte>(size);

	fread(retVal.data(), 1, size, fp);

	fclose(fp);
	return retVal;
}

void HTTPRequestManager::saveImage(const std::vector<Byte>& data, const std::string& file_path)
{
	FILE* fp = NULL;
	fopen_s(&fp, file_path.c_str(), "wb");

	if (!fp)
		throw std::runtime_error("Cannot open image file " + file_path);

	fwrite(data.data(), sizeof(Byte), data.size(), fp);
}



std::string HTTPRequestManager::imageBase64UrlEncode(const std::string& file_path)
{
	auto raw_image = openImage(file_path);
	std::string encoded_image = base64Encode(raw_image.data(), raw_image.size());
	encoded_image = urlEncode(encoded_image);
	return encoded_image;
}

std::string HTTPRequestManager::imageBase64UrlEncode(const std::vector<Byte>& raw_image)
{
	std::string encoded_image = base64Encode(raw_image.data(), raw_image.size());
	encoded_image = urlEncode(encoded_image);
	return encoded_image;
}


// image_format: bmp, jpeg, gif, svg+xml, png
std::string HTTPRequestManager::imageBase64DataUrlScheme(const std::string& file_path)
{
	auto raw_image = openImage(file_path);
	std::string image_format = file_path.substr(file_path.find_last_of('.') + 1);
	if (image_format == "jpg") image_format = "jpeg";
	if (image_format == "svg") image_format = "svg+xml";
	return "data:image/" + image_format + ";base64," + base64Encode(raw_image.data(), raw_image.size());
}

// image_format: bmp, jpeg, gif, svg+xml, png
std::string HTTPRequestManager::imageBase64DataUrlScheme(const std::vector<Byte>& raw_image, const std::string& image_format)
{
	std::string encoded_image = base64Encode(raw_image.data(), raw_image.size());
	return "data:image/" + image_format + ";base64," + base64Encode(raw_image.data(), raw_image.size());
}
