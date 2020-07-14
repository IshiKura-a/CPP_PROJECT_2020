#include "JsonParser.h"
#include "CppCurl.h"
#include <iostream>
#pragma comment(lib,"CppCurl.lib")

int main()
{
	RequestManager manager;

	std::cout << "Testing valid image recognition...\n\n";

	try {
		std::cout << "Using baidu API...\n\n";

		auto s1 = manager->formulaRecognitionBaidu("maxwell.png");

		std::cout << JsonParser::parseCurlReturnValBaidu(s1);

		std::cout << "\n\nUsing mathpix API...\n\n";

		auto s2 = manager->formulaRecognitionMathpix("maxwell.png");

		std::cout << JsonParser::parseCurlReturnValMathpix(s2);
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what();
	}

	std::cout << "\n\nTesting invalid image recognition...\n\n";

	try
	{
		std::cout << "Using baidu API...\n\n";

		auto s1 = manager->formulaRecognitionBaidu("not_an_image.png");

		std::cout << JsonParser::parseCurlReturnValBaidu(s1);

	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what();
	}

	try
	{
		std::cout << "\n\nUsing mathpix API...\n\n";

		auto s2 = manager->formulaRecognitionMathpix("not_an_image.png");

		std::cout << JsonParser::parseCurlReturnValMathpix(s2);

	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what();
	}

	std::cout << "\n\n";

	system("pause");
}