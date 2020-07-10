#include "Encoder.h"
#include <cassert>
#include <stdexcept>

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