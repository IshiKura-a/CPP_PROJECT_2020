#include "../CppCurlDLL/CppCurl.h"
#include <iostream>
#include <fstream>
#pragma comment(lib,"CppCurl.lib")

int main()
{

	RequestManager manager;

	std::string latex = "\\sigma(z)=\\frac{1}{1+e^{-z}}";


	std::cout << "Trying fetching rendered latex formula image...\n\n";
	// get image in buffer

	auto formula_buffer = manager->downloadRenderedFormula(latex, "png");

	std::cout << "Successfully download image in buffer...\n\n";

	manager->saveImage(formula_buffer,"formula_buffer.png");
	
	std::cout << "Successfully save buffer in ./formula_buffer.png\n\n";

	// get image as file
	
	std::cout << "Successfully download image as file in ./formula.png\n\n";
	
	manager->downloadRenderedFormula(latex, "formula.png", "png");


	// test recognition API

	std::cout << "\n\nUsing baidu API...\n\n";

	// using vector<Byte>
	
	auto s = manager->openImage("img.png");

	std::cout << manager->formulaRecognitionBaidu(s) << std::endl;

	std::cout << "\n\nUsing mathpix API...\n\n";

	// using file path
	
	std::cout << manager->formulaRecognitionMathpix("img.png") << std::endl;

	system("pause");
}
