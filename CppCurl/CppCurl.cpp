#include "CppCurl.h"
#include <iostream>
#include <curl/curl.h>
#pragma comment(lib,"libcurl.lib")

const static std::string baidu_request_url = "https://aip.baidubce.com/rest/2.0/ocr/v1/formula";

const static std::string latex_rendering_request_url = "https://latex.codecogs.com/";

static std::string formula_result;

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

// 返回公式识别的结果字符串
// 如果curl的初始化过程中产生错误，抛出runtime_error
// 百度的服务器端产生的错误不会抛出异常，但返回的json string有错误信息
std::string formulaRecognition(const std::string& encoded_image, const std::string& access_token)
{
	std::string url = baidu_request_url + "?access_token=" + access_token;
	CURL* curl = NULL;
	curl_slist* headerlist = NULL;
	CURLcode result_code;

	curl = curl_easy_init();

	if (curl) {

		// https抓包使用
		//curl_easy_setopt(curl, CURLOPT_PROXY, "127.0.0.1:8888");

		// header设置，似乎可以省略
		headerlist = curl_slist_append(headerlist, "Content-Type:application/x-www-form-urlencoded");

		// 打印调试信息
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		// URL地址，需要char*
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

void downloadRenderedFormula(const std::string& latex_string, const std::string& file_path, const std::string& format)
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
