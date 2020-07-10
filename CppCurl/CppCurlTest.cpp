#include "CppCurl.h"
#include "Encoder.h"
#include <iostream>
#include <fstream>

int main()
{

	//std::string latex = "\\sigma(z)=\\frac{1}{1+e^{-z}}";
	//downloadRenderedFormula(latex,"latex_formula.gif","gif");
	//system("pause");

	auto s = imageBase64UrlEncode("img.png");
	s = "image=" + s;
	std::string token = "24.2ab38b35c29d7c52e3ae47ce5c63b328.2592000.1596796408.282335-21194210";
	std::cout << formulaRecognition(s, token) << std::endl;
	system("pause");
}
