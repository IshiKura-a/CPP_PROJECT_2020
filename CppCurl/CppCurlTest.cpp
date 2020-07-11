#include "CppCurl.h"
#include <iostream>
#include <fstream>

#pragma comment(lib,"CppCurl.lib")

int main()
{

	std::string latex = "\\sigma(z)=\\frac{1}{1+e^{-z}}";

	// get image in buffer
	
	std::string formula_str = downloadRenderedFormula(latex,"png");
	std::ofstream ofs("formula_str.png",std::ios::binary);
	for(int i=0;i<formula_str.size();++i)
	ofs<<formula_str[i];
	ofs.close();
	
	// get image as file
	
	downloadRenderedFormula(latex,"formula.png","png");

	// test recognition API
	
	auto s = imageBase64UrlEncode("img.png");
	s = "image=" + s;
	std::string token = "24.2ab38b35c29d7c52e3ae47ce5c63b328.2592000.1596796408.282335-21194210";
	std::cout << formulaRecognition(s, token) << std::endl;
	system("pause");
}
