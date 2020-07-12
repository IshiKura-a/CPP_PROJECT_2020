#include "pch.h"
#include "HTTPRequestManager.h"
#include "TokenDecode.h"
#include <curl/curl.h>
#include <rapidjson/rapidjson.h>
#include <cassert>
#pragma comment(lib,"libcurl.lib")
#pragma comment(lib,"TokenDecode.lib")


const std::string HTTPRequestManager::baidu_request_url = "https://aip.baidubce.com/rest/2.0/ocr/v1/formula";

const std::string HTTPRequestManager::mathpix_request_url = "https://api.mathpix.com/v3/text";

const std::string HTTPRequestManager::latex_rendering_request_url = "https://latex.codecogs.com/";


std::string base64Encode(const char* bytes_to_encode, unsigned int in_len);

std::string base64EncodeDataUrlScheme(const char* bytes_to_encode, unsigned int in_len, const std::string& image_format);

std::string urlEncode(const std::string& bytes_to_encode);

// 用全局函数的写法比较糟糕
// 有时间就修改一下，把ptr内容写到stream上
static size_t callbackFormulaRec(void* ptr, size_t size, size_t nmemb, void* stream)
{
	// 获取到的body存放在ptr中，先将其转换为string格式
	formula_result = std::string((char*)ptr, size * nmemb);
	return size * nmemb;
}

static size_t callbackFormulaRender(void* ptr, size_t size, size_t nmemb, void* stream)
{
	fwrite(ptr, size, nmemb, static_cast<FILE*>(stream));
	return size * nmemb;
}

static size_t callbackFormulaRenderStr(void* ptr, size_t size, size_t nmemb, void* stream)
{
	render_result = std::string((char*)ptr, size * nmemb);
	return size * nmemb;
}

// 返回公式识别的结果字符串
// 如果curl的初始化过程中产生错误，抛出runtime_error
// 百度的服务器端产生的错误不会抛出异常，但返回的json string有错误信息
std::string HTTPRequestManager::formulaRecognitionBaidu(const std::vector<Byte>& raw_image, const std::string& access_token)
{
	CURL* curl = NULL;
	curl_slist* headerlist = NULL;
	CURLcode result_code;


	std::string encoded_image = base64Encode(raw_image.data(), raw_image.size());
	encoded_image = urlEncode(encoded_image);
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
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackFormulaRec);
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
		return formula_result;
	}
	else
	{
		throw std::runtime_error("curl_easy_init() failed.");
	}
}

std::string HTTPRequestManager::formulaRecognitionMathpix(const std::vector<Byte>& raw_image, const std::string& image_format)
{
	CURL* curl = NULL;
	std::string url = mathpix_request_url;
	curl_slist* headerlist = NULL;
	CURLcode result_code;

	std::string encoded_image = base64EncodeDataUrlScheme(raw_image.data(), raw_image.size(),image_format);

	encoded_image = "src=" + encoded_image;

	curl = curl_easy_init();

	if (curl) {

		// header设置
		headerlist = curl_slist_append(headerlist, "Content-Type:application/json");
		headerlist = curl_slist_append(headerlist, "app_id:tmp_key");
		headerlist = curl_slist_append(headerlist, "app_key:ey4fCTFxcjJ3kqbEaH7j23b926HBAux3a98");

		// 打印调试信息
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		// URL地址
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		// 设置POST内容，内容指针encoded_image为char*，注意字符串中要带上表单名称image=
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, encoded_image.c_str());
		// 绑定header
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
		// 设置写函数
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackFormulaRec);
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
		return formula_result;
	}
	else
	{
		throw std::runtime_error("curl_easy_init() failed.");
	}
}


CPPCURL_API void downloadRenderedFormula(const std::string& latex_string, const std::string& file_path, const std::string& format)
{
	std::string url = latex_rendering_request_url + format + ".download?" + latex_string;
	CURL* curl = NULL;
	CURLcode result_code;

	FILE* fp = NULL;
	fopen_s(&fp, file_path.c_str(), "wb");

	curl = curl_easy_init();

	if (curl) {

		// 打印调试信息
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		// URL地址，需要char*
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		// 设置写函数
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackFormulaRender);
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

CPPCURL_API std::string downloadRenderedFormula(const std::string& latex_string, const std::string& format)
{
	std::string url = latex_rendering_request_url + format + ".download?" + latex_string;
	CURL* curl = NULL;
	CURLcode result_code;

	curl = curl_easy_init();

	if (curl) {

		// 打印调试信息
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		// URL地址，需要char*
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		// 设置写函数
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackFormulaRenderStr);

		result_code = curl_easy_perform(curl);
		if (result_code != CURLE_OK)
		{
			std::string errmsg = "curl_easy_perform() failed.";
			errmsg = errmsg + curl_easy_strerror(result_code);
			curl_easy_cleanup(curl);
			throw std::runtime_error(errmsg);
		}
		curl_easy_cleanup(curl);
		return render_result;
	}
	else
	{
		throw std::runtime_error("curl_easy_init() failed.");
	}
}



static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


static inline bool isBase64(const char c)
{
	return (isalnum(c) || (c == '+') || (c == '/'));
}

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

// image_format: bmp, jpeg, gif, svg+xml, png
std::string base64EncodeDataUrlScheme(const char* bytes_to_encode, unsigned int in_len, const std::string& image_format)
{
	return "data:image/"+image_format+";base64,"+base64Encode(bytes_to_encode,in_len);
}

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
			strTemp += "+";
		else
		{
			strTemp += '%';
			strTemp += decToHex(bytes_to_encode[i] >> 4);
			strTemp += decToHex(bytes_to_encode[i] % 16);
		}
	}
	return strTemp;
}

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

// 普通指针注意, 不要在代码中使用这个函数
[[nodiscard]] char* readImage(const std::string& file_path, int* f_size)
{
	FILE* fp = NULL;
	fopen_s(&fp, file_path.c_str(), "rb");

	if (!fp)
		throw std::runtime_error("Cannot open image file " + file_path);

	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	*f_size = size;
	rewind(fp);

	char* buffer = new char[size]();
	int s = fread(buffer, 1, size, fp);

	fclose(fp);
	return buffer;
}


std::string imageBase64UrlEncode(const std::string& file_path)
{
	int size;
	char* p = readImage(file_path, &size);
	std::string str = base64Encode(p, size);
	str = urlEncode(str);
	delete[]p;
	return str;
}