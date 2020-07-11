#include "CppCurl.h"
#include <iostream>
#include <fstream>

#pragma comment(lib,"CppCurl.lib")

int main()
{

	//std::string latex = "\\sigma(z)=\\frac{1}{1+e^{-z}}";
	//downloadRenderedFormula(latex,"latex_formula.gif","gif");
	//system("pause");

	auto s = imageBase64UrlEncode("img.png");
	s = "image=" + s;
	std::string token = "7A4F0C7C6D1AA836183C6245AF5A546D\
CA62994D2AD6DF01083A5170573825F8\
869CE35BD9C4A5770C63CCD9A59CBE5B\
D63F06E28A2AA8D4251B7222F3DC52BE\
CACE6DD82CDB6F51353347977A16371B";
	std::cout << formulaRecognition(s, token) << std::endl;
	system("pause");
}
