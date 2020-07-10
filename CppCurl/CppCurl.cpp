#include "CppCurl.h"
#include <iostream>
#include <curl/curl.h>
#pragma comment(lib,"libcurl.lib")

const static std::string baidu_request_url = "https://aip.baidubce.com/rest/2.0/ocr/v1/formula";

const static std::string latex_rendering_request_url = "https://latex.codecogs.com/";

static std::string formula_result;

// ��ȫ�ֺ�����д���Ƚ����
// ��ʱ����޸�һ�£���ptr����д��stream��
static size_t callbackFormulaRec(void* ptr, size_t size, size_t nmemb, void* stream)
{
	// ��ȡ����body�����ptr�У��Ƚ���ת��Ϊstring��ʽ
	formula_result = std::string((char*)ptr, size * nmemb);
	return size * nmemb;
}

static size_t callbackFormulaRender(void* ptr, size_t size, size_t nmemb, void* stream)
{
	fwrite(ptr, size, nmemb, static_cast<FILE*>(stream));
	return size * nmemb;
}

// ���ع�ʽʶ��Ľ���ַ���
// ���curl�ĳ�ʼ�������в��������׳�runtime_error
// �ٶȵķ������˲����Ĵ��󲻻��׳��쳣�������ص�json string�д�����Ϣ
std::string formulaRecognition(const std::string& encoded_image, const std::string& access_token)
{
	std::string url = baidu_request_url + "?access_token=" + access_token;
	CURL* curl = NULL;
	curl_slist* headerlist = NULL;
	CURLcode result_code;

	curl = curl_easy_init();

	if (curl) {

		// httpsץ��ʹ��
		//curl_easy_setopt(curl, CURLOPT_PROXY, "127.0.0.1:8888");

		// header���ã��ƺ�����ʡ��
		headerlist = curl_slist_append(headerlist, "Content-Type:application/x-www-form-urlencoded");

		// ��ӡ������Ϣ
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		// URL��ַ����Ҫchar*
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		// ����POST���ݣ�����ָ��encoded_imageΪchar*��ע���ַ�����Ҫ���ϱ�����image=
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, encoded_image.c_str());
		// ��header
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
		// ����д����
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackFormulaRec);
		// ���ñ��β���ΪPOST
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		// ���ñ��β���ʹ��header
		curl_easy_setopt(curl, CURLOPT_HEADER, 1);
		// ����callback�����ĵ��ĸ�����Ϊdata_ptr
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

		// ��ӡ������Ϣ
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		// URL��ַ����Ҫchar*
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		// ����д����
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackFormulaRender);
		// ����д����д���ָ��
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
