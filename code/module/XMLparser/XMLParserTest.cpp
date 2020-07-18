#include "XMLparser.h"
#include "CppCurl.h"
#include <iostream>
#pragma comment(lib,"CppCurl.lib")
#pragma comment(lib,"tinyxml2.lib")

int main()
{
	RequestManager manager;
	std::string latex = "\\frac{1}{3.2^2}";
	
	std::cout << "Test calculate latex result...\n\n";
	std::cout << "latex = " << latex << "\n\n";


	std::cout << "xml = \n";
	std::string xml = manager->getFormulaResult(latex);
	std::cout << xml;


	std::cout << "\nresult = ";
	std::cout << XMLParser::parseCurlResult(xml) << "\n\n";
	system("pause");
	
}