#ifdef CPPCURL_EXPORTS
#define CPPCURL_API __declspec(dllexport)
#else
#define CPPCURL_API __declspec(dllimport)
#endif

#include <string>

// @param:
// encoded_image: ��Ҫ���й�ʽʶ���ͼƬ�Ƕ���������. ͼƬ������Ҫbase64���벢����urlencode.
// access_token: ���ðٶ�API��Ҫ��token.
// @return:
// ��ʽʶ����,json��ʽ.
CPPCURL_API std::string formulaRecognition(const std::string& encoded_image, const std::string& access_token);

// @param:
// latex_string: ��Ҫ��Ⱦ��latex string. ע��ɾ�����пհ��ַ�.
// file_path: ������Ⱦ��ͼƬ��·��.
// format: ����ͼƬ�ĸ�ʽ. ֧��gif, svg, png.
CPPCURL_API void downloadRenderedFormula(const std::string& latex_string, const std::string& file_path, const std::string& format);

// @param:
// latex_string: ��Ҫ��Ⱦ��latex string. ע��ɾ�����пհ��ַ�.
// format: ����ͼƬ�ĸ�ʽ. ֧��gif, svg, png.
// @return:
// ���صĶ������ļ�. string������ת��data�Ĺ���, ʵ�ʴ洢���Ƕ�����data, *����*��Ҫ����stringʹ��.
// ��Ҫʹ�ø�����ʱ��ʹ��.c_str()���data pointer.
CPPCURL_API std::string downloadRenderedFormula(const std::string& latex_string,const std::string& format);

// @param:
// file_path: ͼ��·��
// @return:
// ͼ�񾭹�base64����, urlencode���string
CPPCURL_API std::string imageBase64UrlEncode(const std::string& file_path);


CPPCURL_API std::string imageBase64(const std::string& file_path, const std::string& image_format);


CPPCURL_API std::string formulaRecognitionMathpix(const std::string& encoded_image);